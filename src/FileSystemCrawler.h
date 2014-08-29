#ifndef __FILE_SYSTEM_CRAWLER_H
#define __FILE_SYSTEM_CRAWLER_H

#include <list>

class FileSystemCrawler
{
public:
	FileSystemCrawler()
	{ }

	~FileSystemCrawler()
	{ }

	std::list<std::string> crawl(const std::list<std::string> &dirs);
};

#endif
