#include <boost/program_options.hpp>

#include <iostream>
#include "Actions/TraceAction.h"
#include "Actions/FileAction.h"
#include "FileSystemCrawler.h"

namespace po = boost::program_options;

class MyCLass {
  int *pInt;
public:
  MyCLass() {
    pInt = new int;
    *pInt = 42;
  }
  ~MyCLass() {
    delete pInt;
    printf("Goodbye cruel world!");
  }
  void func1() {
    printf("Hello World %d", *pInt);
  }
};


int main(int argc, char **argv)
{
  po::options_description description("Hash Generator usage");
  description.add_options()
    ("help", "show help")
    ("help-generator,h", po::value<std::string>(), "Help for generators. Possible values = [file, trace]")
    ("dir,d", po::value< std::vector<std::string>>(), "directories to compute hash")
    ("file_pattern,p", po::value<std::string>()->default_value(".*"), "Pattern on which performing checksum")
    ("generator,g", po::value<std::string>(), "name of the generator. Posible values = [file, trace]")
    ("level", po::value<int>(), "Recursive level");

  po::variables_map vm;

  po::parsed_options parsed =
    po::command_line_parser(argc, argv).options(description).allow_unregistered().run();

  po::store(parsed, vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << description << std::endl;
    return 0;
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

    if (dirs.size() == 0)
      return 0;
  }


  std::string generator;
  if (vm.count("generator"))
  {
    generator = vm["generator"].as<std::string>();

    if (generator == "file")
    {
      FileSystemCrawler<FileAction> crawler(argc, argv);
      crawler.crawl(dirs);
    }
    else if (generator == "trace")
    {
      FileSystemCrawler<TraceAction> crawler(argc, argv);
      crawler.crawl(dirs);
    }
  }

	return 0;
}