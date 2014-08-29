#include "FileSystemCrawler.h"

int main(int argc, char **argv)
{
	FileSystemCrawler crawler;


	std::list<std::string> dirs;

	//dirs.push_front("D:\\dev\\monitor\\10.9.dev\\TEST_MONITOR\\Bin_Release");

	crawler.crawl(dirs);


	return 0;
}