#ifndef __SEPARATE_FILE_ACTION_H
#define __SEPARATE_FILE_ACTION_H

#include <fstream>
#include <map>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

namespace po = boost::program_options;

struct MultipleFileAction
{
private:
  po::options_description parameters;
  std::map<std::string, file> _files;
  std::vector<std::string> _directories;

  std::string root;

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
  MultipleFileAction(int argc, char **argv)
    : parameters("Multiple File Generator")
  {
    parameters.add_options()
    ("help", "Help");

    po::variables_map vm;
    po::parsed_options parsed =
      po::command_line_parser(argc, argv).options(parameters).allow_unregistered().run();

    po::store(parsed, vm);
    po::notify(vm);
  }

  ~MultipleFileAction()
  {}

  void set_root(const std::string &root)
  {
    this->root = root;
    _directories.push_back(sys::path(root).filename());
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

    std::string dir = path.parent_path();


    std::string output = path.basename() + ".md5";
    sys::path _full_path = sys::path(dir) / sys::path(output);


    std::ofstream out_file(_full_path, std::ios::out);
    out_file << md5 << std::endl;
  }

  const po::options_description& options()
  {
    return parameters;
  }

  friend std::ostream &operator<< (std::ostream &os, const MultipleFileAction &action)
  {
    os << action.parameters;
    return os;
  }
};

#endif
