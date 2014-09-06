#include <boost/program_options.hpp>

#include <iostream>
#include "Actions/TraceAction.h"
#include "Actions/FileAction.h"
#include "FileSystemCrawler.h"

namespace po = boost::program_options;

int main(int argc, char **argv)
{
  po::options_description description("Hash Generator usage");
  description.add_options()
    ("help", "show help")
    ("help-generator,h", po::value<std::string>(), "Help for generators. Possible values = [file, trace]")
    ("dir,d", po::value< std::vector<std::string> >(), "directories to compute hash")
    ("generator,g", po::value<std::string>(), "name of the generator. Posible values = [file, trace]")
    ("level", po::value<int>(), "Recursive level");


  /*FileAction fAction;
  po::options_description file_options = fAction.options();

  TraceAction tAction;
  po::options_description trace_options = tAction.options();*/

  //description.add(file_options).add(trace_options);

  po::variables_map vm;
  //po::store(po::parse_command_line(argc, argv, description), vm);

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