#ifndef __TRACE_ACTION_H
#define __TRACE_ACTION_H

#include <filesystem>
#include <iostream>

namespace sys = std::tr2::sys;

struct TraceAction
{
public:
  void do_directory(const sys::path &path)
  {
    std::cout << path.leaf() << std::endl;
  }

  void do_file(const std::string& tabs,
               sys::path &path, const std::string& md5)
  {
    std::string name(path.leaf());
    std::string full_path(path.file_string());

    std::cout << tabs << name << " " << md5 << std::endl;
  }
};

#endif
