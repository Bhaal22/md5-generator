#ifndef __FILE_SYSTEM_CRAWLER_H
#define __FILE_SYSTEM_CRAWLER_H

class FileSystemCrawler
{
public:
	FileSystemCrawler()
	{ }

	~FileSystemCrawler()
	{ }

	std::vector<std::string> crawl(const std::vector<std::string> &dirs);
};

#endif
