#include <boost/program_options.hpp>

#include <iostream>
#include "file.h"

#include "Actions/TraceAction.h"
#include "Actions/MultipleFileAction.h"
#include "Actions/SingleFileAction.h"
#include "FileSystemCrawler.h"

namespace po = boost::program_options;

int main(int argc, char **argv)
{
  po::options_description description("Hash Generator usage");
  description.add_options()
    ("help", "show help")
    ("help-generator,h", po::value<std::string>(), "Help for generators. Possible values = [singlefile, multiplefile, trace]")
    ("dir,d", po::value< std::vector<std::string>>(), "directories to compute hash")
    ("file_pattern,p", po::value<std::string>()->default_value(".*"), "Pattern on which performing checksum")
    ("generator,g", po::value<std::string>(), "name of the generator. Posible values = [singlefile, multiplefile, trace]")
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

  std::string pattern;
  if (vm.count("file_pattern"))
  {
    pattern = vm["file_pattern"].as<std::string>();

    try
    {
      std::tr1::regex rx(pattern);
    }
    catch (std::regex_error ex)
    {
      std::cout << "pattern invalid" << std::endl;
      std::cout << ex.what() << std::endl;
      return 0;
    }
  }

  std::string help_generator;
  if (vm.count("help-generator"))
  {
    help_generator = vm["help-generator"].as<std::string>();

    if (help_generator == "singlefile")
    {
      SingleFileAction action(argc, argv);
      std::cout << action << std::endl;
      return 0;
    }
    else if (help_generator == "multiplefile")
    {
      MultipleFileAction action(argc, argv);
      std::cout << action << std::endl;
      return 0;
    }
    else if (help_generator == "trace")
    {
      TraceAction action(argc, argv);
      std::cout << action << std::endl;
      return 0;
    }
  }


  std::string generator;
  if (vm.count("generator"))
  {
    generator = vm["generator"].as<std::string>();

    if (generator == "singlefile")
    {
      FileSystemCrawler<SingleFileAction> crawler(argc, argv, pattern);
      crawler.crawl(dirs);
    }
    else if (generator == "multiplefile")
    {
      FileSystemCrawler<MultipleFileAction> crawler(argc, argv, pattern);
      crawler.crawl(dirs);
    }
    else if (generator == "trace")
    {
      FileSystemCrawler<TraceAction> crawler(argc, argv, pattern);
      crawler.crawl(dirs);
    }
  }

	return 0;
}