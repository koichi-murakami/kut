/*============================================================================
  Copyright 2017-2021 Koichi Murakami

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file License for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include <getopt.h>
#include "jsonparser.h"

namespace {
// --------------------------------------------------------------------------
void show_version()
{
  std::cout << "jparser version 1.0.0" << std::endl;
}

// --------------------------------------------------------------------------
void show_help()
{
  std::cout << "j5parser - JSON5 parser" << std::endl;
  std::cout << "usage:" << std::endl;
  std::cout << "j5parser [options] [JSON5 file]"
            << std::endl << std::endl;
  std::cout << "   -h, --help          show this message." << std::endl
            << "   -v  --version       show program name/version." << std::endl
            << std::endl;
  std::cout << std::endl;
}

} // end of namespace

using namespace kut;

// --------------------------------------------------------------------------
int main(int argc, char** argv)
{
  // optional parameters
  bool qhelp = false;
  bool qversion = false;

  struct option long_options[] = {
    {"help",    no_argument,       NULL, 'h'},
    {"version", no_argument,       NULL, 'v'},
    {NULL,      0,                 NULL,  0}
  };

  int c;
  while (1) {
    int option_index = -1;

    c = getopt_long(argc, argv, "hv", long_options, &option_index);

    if (c == -1) break;

    switch (c) {
    case 'h' :
      qhelp = true;
      break;
    case 'v' :
      qversion = true;
      break;
    default:
      std::exit(EXIT_FAILURE);
      break;
    }
  }

  if ( qhelp ) {
    ::show_help();
  }

  if ( qversion ) {
    ::show_version();
  }

  if ( qhelp || qversion ) {
    std::exit(EXIT_SUCCESS);
  }

  // config file
  std::string config_file = "";
  if ( optind < argc ) {
    config_file = argv[optind];
  } else {
    ::show_help();
    std::exit(EXIT_FAILURE);
  }

  // ----------------------------------------------------------------------
  // parsing config JSON file...
  JsonParser* jparser = JsonParser::GetJsonParser();
  bool qload = jparser-> LoadFile(config_file);
  if ( ! qload ) {
    std::cout << "[ERROR] failed on loading a config file. "
              << config_file << std::endl;
    std::exit(EXIT_FAILURE);
  }

  qload = jparser-> LoadFile(config_file, "JSON-B");
  if ( ! qload ) {
    std::cout << "[ERROR] failed on loading a config file. "
              << config_file << std::endl;
    std::exit(EXIT_FAILURE);
  }

  jparser-> SelectJsonData("JSON-B");

  // ----------------------------------------------------------------------
  std::cout << "------------------------------" << std::endl;
  std::cout << "@@@ dump JSON data" << std::endl;
  jparser-> DumpAll();
  std::cout << "------------------------------" << std::endl;

  std::cout << "@@@ yes/no = "
            <<  jparser-> GetBoolValue("yesorno") << std::endl;

  std::vector<bool> ynlist;
  jparser-> GetBoolArray("yesorno_list", ynlist);
  std::cout << "@@@ yes/no list = ["
            << ynlist[0] << ", " << ynlist[1] << "]" << std::endl;

  std::cout << "@@@ Primary/type = "
            <<  jparser-> GetStringValue("Primary/type") << std::endl;

  std::cout << "@@@ Primary/number = "
            << jparser-> GetIntValue("Primary/number") << std::endl;

  std::vector<std::string> legend;
  jparser-> GetStringArray("Primary/legend", legend);
  std::cout << "@@@ Primary/legend = ["
            << legend[0] << ", " << legend[1] << ", "
            << legend[2] << "]" << std::endl;

  std::cout << "@@@ Geometry/size = "
            << jparser-> GetDoubleValue("Geometry/size") << std::endl;

  std::cout << "@@@ Geometry/type/name = "
            << jparser-> GetStringValue("Geometry/type/name") << std::endl;

  std::vector<int> segment;
  jparser-> GetIntArray("Geometry/segment", segment);
  std::cout << "@@@ Geometry/segment = ["
            << segment[0] << ", " << segment[1] << ", "
            << segment[2] << "]" << std::endl;

  std::vector<double> position;
  jparser-> GetDoubleArray("Geometry/position", position);
  std::cout << "@@@ Geometry/position = ["
            << position[0] << ", " << position[1] << ", "
            << position[2] << "]" << std::endl;

  return EXIT_SUCCESS;
}
