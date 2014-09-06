#ifndef __FILE_ACTION_H
#define __FILE_ACTION_H

#include <fstream>
#include <map>

#include <boost/filesystem.hpp>

namespace po = boost::program_options;

struct FileAction
{
private:
  std::map<std::string, std::string> _files;
  std::vector<std::string> _directories;

public:
  ~FileAction()
  {
    std::ofstream out_file("md5.out", std::ios::out);

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
    std::for_each(keys.begin(), keys.end(),
      [&out_file, &map_files](const std::string& name) 
      {
        out_file << map_files[name] << " *" << name << std::endl;
      });


    out_file.close();
  }

  void do_directory(const sys::path &path)
  {
    std::string name(path.leaf());

    _directories.push_back(name);
  }

  void do_file(sys::path &path, const std::string& md5)
  {
    std::string name(path.leaf());
    std::string full_path(path.file_string());

    _files[full_path] = md5;
  }

  po::options_description options()
  {
    po::options_description config("File Generator");
    config.add_options()
      ("help", "Help")
      ("output_file,o", po::value<std::string>(), "Output File");


    return config;
  }
};

#endif
