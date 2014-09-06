#ifndef __TRACE_ACTION_H
#define __TRACE_ACTION_H

#include <string>
#include <filesystem>
#include <iostream>

#include <boost/filesystem.hpp>

namespace sys = std::tr2::sys;
namespace po = boost::program_options;

struct TraceAction
{
private:
  std::string tabs;
public:
  void do_directory(const sys::path &path)
  {
    tabs += " ";
    std::cout << path.leaf() << std::endl;
  }

  void do_file(sys::path &path, const std::string& md5)
  {
    std::string name(path.leaf());
    std::string full_path(path.file_string());

    std::cout << tabs << name << " " << md5 << std::endl;
  }

  po::options_description options()
  {
    po::options_description config("Configuration Trace");
    config.add_options()
      ("optimization", po::value<int>()->default_value(10),
      "optimization level")
      ("include-path,I",
      po::value< std::vector<std::string> >()->composing(),
      "include path");

    return config;
  }
};

#endif
