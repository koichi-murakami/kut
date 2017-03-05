/*============================================================================
  CUGEANT4 - CUDA Geant4 Project
  Copyright 2012 [[@copyright]]

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include <fstream>
#include <iostream>
#include <string>
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include "jsonparser.h"

using namespace kut;

// --------------------------------------------------------------------------
const std::string json_string = R"(// JSON5 test pattern
{
  // global parameters
  yesorno : true,
  yesorno_list : [ true, false],

  // -----------------------------------------------------------------
  // primary setting
  "Primary" : {
    // primary type (gun / beam)
    type : 'gun',
    number : 100,

    // particle starting position (x,y,z) in cm (z >= -100)
    position : [ 5., +.1, +100. ],

    legend : ["x1", "y2", "z3"],
  },

  // -----------------------------------------------------------------
  // geometry setup
  Geometry : {
    /* geometry size */
    size : 20.0,

    segment : [5, 105, 25],

    // position in different namespace
    position : [ 1., 1., 0. ],

    // sub objects
    type : {
      name : "calorimeter A",
    },
  },
}
)";

// --------------------------------------------------------------------------
TEST_GROUP(JsonParser)
{
  void setup() {
    JsonParser* jparser = JsonParser::GetJsonParser();
    jparser-> LoadFile("sample.json5");
  }

  void teardown() { }
};

// --------------------------------------------------------------------------
TEST(JsonParser, Parse)
{
  JsonParser* jparser = JsonParser::GetJsonParser();
  CHECK(jparser-> LoadFile("sample.json5"));
}

// --------------------------------------------------------------------------
TEST(JsonParser, Contains)
{
  JsonParser* jparser = JsonParser::GetJsonParser();
  CHECK_FALSE(jparser-> Contains("hoge"));
  CHECK(jparser-> Contains("yesorno"));
  CHECK(jparser-> Contains("yesorno_list"));
  CHECK(jparser-> Contains("Primary"));
  CHECK(jparser-> Contains("Primary/type"));
  CHECK(jparser-> Contains("Primary/number"));
}

// --------------------------------------------------------------------------
TEST(JsonParser, Values)
{
  JsonParser* jparser = JsonParser::GetJsonParser();
  CHECK_EQUAL(true, jparser-> GetBoolValue("yesorno"));
  std::string sval = jparser-> GetStringValue("Primary/type");
  STRCMP_EQUAL("gun", sval.c_str());
  CHECK_EQUAL(100, jparser-> GetIntValue("Primary/number"));
  std::vector<int> ivec;
  jparser->GetIntArray("Geometry/segment", ivec);
  CHECK_EQUAL(5, ivec[0]);
  std::vector<double> dvec;
  jparser-> GetDoubleArray("Geometry/position", dvec);
  DOUBLES_EQUAL(1.0, dvec[0], 1.E-6);
}

// --------------------------------------------------------------------------
int main(int argc, char** argv)
{
  std::ofstream ofile("sample.json5");
  ofile << json_string;
  ofile.close();

  MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
  return RUN_ALL_TESTS(argc, argv);
}
