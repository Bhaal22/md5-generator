#include <boost/program_options.hpp>

#include <iostream>
#include "FileSystemCrawler.h"

namespace po = boost::program_options;

int main(int argc, char **argv)
{
  po::options_description description("Hash Generator usage");
  description.add_options()
    ("help", "show help")
    ("dir,d", po::value< std::vector<std::string> >(), "directories to compute hash")
    ("level", "recursive level");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, description), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << description << std::endl;
    return 1;
  }

  int level = -1;
  if (vm.count("level"))
  {
    level = vm["level"].as<int>();
  }

  

  std::vector<std::string> dirs;
  if (vm.count("dir"))
  {
    dirs = vm["dir"].as< std::vector< std::string> >();
  }



	FileSystemCrawler crawler;
	crawler.crawl(dirs);


	return 0;
}