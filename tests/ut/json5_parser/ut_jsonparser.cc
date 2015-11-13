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
#include "gtest/gtest.h"
#include "jsonparser.h"

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
TEST(JsonParser, Parse)
{
  klab::JsonParser* jparser = klab::JsonParser::GetJsonParser();
  EXPECT_TRUE(jparser-> LoadFile("sample.json5"));
}

// --------------------------------------------------------------------------
TEST(JsonParser, DumpAll)
{
  klab::JsonParser* jparser = klab::JsonParser::GetJsonParser();
  jparser-> DumpAll();
  SUCCEED();
}

// --------------------------------------------------------------------------
TEST(JsonParser, Contains)
{
  klab::JsonParser* jparser = klab::JsonParser::GetJsonParser();
  EXPECT_FALSE(jparser-> Contains("hoge"));
  EXPECT_TRUE(jparser-> Contains("yesorno"));
  EXPECT_TRUE(jparser-> Contains("yesorno_list"));
  EXPECT_TRUE(jparser-> Contains("Primary"));
  EXPECT_TRUE(jparser-> Contains("Primary/type"));
  EXPECT_TRUE(jparser-> Contains("Primary/number"));
}


// --------------------------------------------------------------------------
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  std::ofstream ofile("sample.json5");
  ofile << json_string;
  ofile.close();

  int rc = RUN_ALL_TESTS();

  return rc;
}
