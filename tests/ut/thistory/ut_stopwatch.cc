/*============================================================================
  Copyright 2017-2021 Koichi Murakami

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file License for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include <stdlib.h>
#include "stopwatch.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

using namespace kut;

// --------------------------------------------------------------------------
namespace {
double do_something()
{
  double x {0.};
  for (auto i = 0; i < 10000; i++) {
    for (auto j = 0; j < 10000; j++) x += rand()/(double)RAND_MAX - 0.5;
  }
  return x;
}

} // end of namespace

// --------------------------------------------------------------------------
TEST_GROUP(Stopwatch)
{
  void setup() { }
  void teardown() { }
};

// --------------------------------------------------------------------------
TEST(Stopwatch, Split)
{
  auto sw = new Stopwatch();
  ::do_something();
  sw-> Split();
  delete sw;
}

// --------------------------------------------------------------------------
TEST(Stopwatch, GetRealElapsed)
{
  auto sw = new Stopwatch();
  ::do_something();
  sw-> Split();
  auto t = sw-> GetRealElapsed();
  CHECK(t>0.);
  delete sw;
}

// --------------------------------------------------------------------------
TEST(Stopwatch, GetSystemElapsed)
{
  auto sw = new Stopwatch();
  ::do_something();
  sw-> Split();
  auto t = sw-> GetSystemElapsed();
  CHECK(t>=0.);
  delete sw;
}

// --------------------------------------------------------------------------
TEST(Stopwatch, GeUserlElapsed)
{
  auto sw = new Stopwatch();
  ::do_something();
  sw-> Split();
  auto t = sw-> GetUserElapsed();
  CHECK(t>0.);
  delete sw;
}

// --------------------------------------------------------------------------
TEST(Stopwatch, GeClockTime)
{
  auto sw = new Stopwatch();
  auto current_time = sw-> GetClockTime();
  delete sw;
}

// --------------------------------------------------------------------------
int main(int argc, char** argv)
{
  return RUN_ALL_TESTS(argc, argv);
}
