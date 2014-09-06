#ifndef __FILE_ACTION_H
#define __FILE_ACTION_H

#include <fstream>
#include <map>

#include <boost/filesystem.hpp>

namespace po = boost::program_options;

struct FileAction
{
private:
  po::options_description parameters;
  std::map<std::string, std::string> _files;
  std::vector<std::string> _directories;

  std::string root;
  std::string output_file;


  sys::path relativePath(const sys::path &path, const sys::path &relative_to)
  {
    // create absolute paths
    sys::path p = path;
    sys::path r = relative_to;

    // if root paths are different, return absolute path
    if (p.root_path() != r.root_path())
      return p;

    // initialize relative path
    sys::path result;

    // find out where the two paths diverge
    sys::path::const_iterator itr_path = p.begin();
    sys::path::const_iterator itr_relative_to = r.begin();
    while (*itr_path == *itr_relative_to && itr_path != p.end() && itr_relative_to != r.end()) {
      ++itr_path;
      ++itr_relative_to;
    }

    // add "../" for each remaining token in relative_to
    if (itr_relative_to != r.end()) {
      ++itr_relative_to;
      while (itr_relative_to != r.end()) {
        result /= "..";
        ++itr_relative_to;
      }
    }

    // add remaining path
    while (itr_path != p.end()) {
      result /= *itr_path;
      ++itr_path;
    }

    return result;
  }

public:
  FileAction(int argc, char **argv)
    : parameters("File Generator")
  {
    parameters.add_options()
      ("help", "Help")
      ("output_file,o", po::value<std::string>(), "Output File");

    po::variables_map vm;
    po::parsed_options parsed =
      po::command_line_parser(argc, argv).options(parameters).allow_unregistered().run();

    po::store(parsed, vm);
    po::notify(vm);


    if (vm.count("output_file"))
    {
      output_file = vm["output_file"].as<std::string>();
    }

  }

  ~FileAction()
  {
    std::ofstream out_file(output_file, std::ios::out);

    out_file << "//----- Directories -----\\\\" << std::endl;
    std::for_each(_directories.begin(), _directories.end(),
      [&out_file](std::string directory) {

      out_file << "// **** " << directory << " **** \\\\" << std::endl;
    });

    std::vector<std::string> keys(_files.size());

    std::transform(_files.begin(), _files.end(), keys.begin(),
        [](std::pair<std::string, std::string> p) {
      return p.first;
    });


    std::map<std::string, std::string> &map_files = _files;
    std::sort(keys.begin(), keys.end());

    sys::path _root(root);
    std::for_each(keys.begin(), keys.end(),
      [&out_file, &map_files, &_root, this](const std::string& name) 
      {
        sys::path p = relativePath(sys::path(name), _root);
        out_file << map_files[name] << " *" << _root.filename() + "/" + p.file_string() << std::endl;
      });


    out_file.close();
  }

  void set_root(const std::string &root)
  {
    this->root = root;
  }

  void do_directory(const sys::path &path)
  {
    std::string name(path.filename());

    sys::path root_path = sys::path(root);
    sys::path p = relativePath(path, root_path);
    _directories.push_back(root_path.filename() + "/" + p.file_string());
  }

  void do_file(sys::path &path, const std::string& md5)
  {
    std::string name(path.leaf());
    std::string full_path(path.file_string());

    _files[full_path] = md5;
  }

  const po::options_description& options()
  {
    return parameters;
  }
};

#endif
