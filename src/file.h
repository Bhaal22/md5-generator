#ifndef _FILE_H
#define _FILE_H

#include <iostream>

struct file
{
  std::string root;
  std::string md5;

  file()
    : root(""), md5("")
  { }

  file(const std::string &root, const std::string &md5)
    : root(root), md5(md5)
  { }
};

#endif
