#include <boost/program_options/options_description.hpp>

#include <iostream>
#include "FileSystemCrawler.h"

namespace po = boost::program_options;

int main(int argc, char **argv)
{
  po::options_description description("Hash Generator usage");




	FileSystemCrawler crawler;


	std::list<std::string> dirs;

	dirs.push_front("D:\\dev\\monitor\\10.9.dev\\TEST_MONITOR\\Bin");

	crawler.crawl(dirs);


	return 0;
}