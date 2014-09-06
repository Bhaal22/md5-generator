#ifndef __FILE_SYSTEM_CRAWLER_H
#define __FILE_SYSTEM_CRAWLER_H

#include "_md5.h"

template <typename _Action>
class FileSystemCrawler
{
private:
  _Action _action;
public:
	FileSystemCrawler(int argc, char **argv)
    : _action(argc, argv)
	{ }

	~FileSystemCrawler()
	{ }

  std::vector<std::string> crawl(const std::vector<std::string> &dirs)
  {
    std::for_each(dirs.begin(), dirs.end(),
                  list_files<_Action>(_action, ".*\\.dll", 0));
    return std::vector<std::string>();
  }
};

#endif
