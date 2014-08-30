//#include <boost/program_options/option.hpp>

#include <iostream>
#include "FileSystemCrawler.h"

int main(int argc, char **argv)
{
	FileSystemCrawler crawler;


	std::list<std::string> dirs;

  std::cout << "coucou" << std::endl;
	dirs.push_front("D:\\dev\\monitor\\10.9.dev\\TEST_MONITOR\\Bin");

	crawler.crawl(dirs);


	return 0;
}