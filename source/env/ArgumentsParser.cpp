#include <radix/env/ArgumentsParser.hpp>

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <getopt.h>
#include <iostream>

#include <radix/core/file/Path.hpp>
#include <radix/env/Config.hpp>
#include <radix/env/Environment.hpp>

namespace radix {
std::string ArgumentsParser::mapName = "";
std::string ArgumentsParser::mapPath = "";

void ArgumentsParser::setEnvironmentFromArgs(const int argc, char **argv) {
  static struct option long_options[] = {
    {"version",          no_argument,       0, 'v'},
    {"help",             no_argument,       0, 'h'},
    {"datadir",          required_argument, 0, 'd'},
    {"map",              required_argument, 0, 'm'},
    {"mapfrompath",      required_argument, 0, 'M'},
    {0, 0, 0, 0}
  };

  while (1) {
    int option_index = 0;
    int argument;
    argument = getopt_long (argc, argv, "vhd:m:M:", long_options, &option_index);

    if (argument == -1) {
      break;
    }

    /// Command Line arguments
    switch (argument) {
    case 'v':
      /// - version \n
      /// Display the current version.
      std::cout << "GlPortal Version 0.1\n";
      exit(0);
    case 'd':
      /// - datadir \n
      /// Set directory where the game data is stored.
      Environment::setDataDir(optarg);
      break;
    case 'h':
      /// - help \n
      /// Display the help.
      std::cout << "Usage: glportal [options]" << std::endl << std::endl;

      std::cout << "Options:" << std::endl;
      std::cout << "  -h, --help               Show this help message and exit" << std::endl;
      std::cout << "  -v, --version            Display GlPortal version" << std::endl;
      std::cout << "  -d, --datadir DIR        Set the data directory" << std::endl;
      std::cout << "  -m, --map NAME           Specify map name to load" << std::endl;
      std::cout << "  -M, --mapfrompath FILE   Load the specified map file" << std::endl;

      exit(0);
    case 'm':
      /// - map \n
      /// Set the map that should be loaded.
      mapName = optarg;
      break;
    case 'M':
      /// - mapFromPath \n
      /// Set the map that should be loaded.
      mapPath = optarg;
    default:
      break;
    }
  }
}

void ArgumentsParser::populateConfig() {
  Config &config = Environment::getConfig();
  if (not mapName.empty()) {
    config.map = mapName;
  }
  if (not mapPath.empty()) {
    config.mapPath = mapPath;
  }
}

} /* namespace radix */
