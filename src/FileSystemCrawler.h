#ifndef __FILE_SYSTEM_CRAWLER_H
#define __FILE_SYSTEM_CRAWLER_H

#include "_md5.h"

template <typename _Action>
class FileSystemCrawler
{
public:
	FileSystemCrawler()
	{ }

	~FileSystemCrawler()
	{ }

  std::vector<std::string> crawl(const std::vector<std::string> &dirs)
  {
    std::for_each(dirs.begin(), dirs.end(),
      list_files<_Action>(""));
    return std::vector<std::string>();
  }
};

#endif
