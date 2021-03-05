/*============================================================================
  Copyright 2017 Koichi Murakami

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file License for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include <stdlib.h>
#include "timehistory.h"
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
TEST_GROUP(TimeHistory)
{
  void setup() {
    auto th = TimeHistory::GetTimeHistory();
  }
  void teardown() { }
};

// --------------------------------------------------------------------------
TEST(TimeHistory, TakeSplitAndFind)
{
  auto th = TimeHistory::GetTimeHistory();
  ::do_something();
  th-> TakeSplit("TakeSplitAndFind");
  CHECK(th-> FindAKey("TakeSplitAndFind"));
  CHECK_FALSE(th-> FindAKey("hoge"));
}

// --------------------------------------------------------------------------
TEST(TimeHistory, GetTime)
{
  auto th = TimeHistory::GetTimeHistory();
  ::do_something();
  th-> TakeSplit("GetTime");
  double t = th-> GetTime("GetTime");
  CHECK(t>0.);
  t = th-> GetTime("hoge");
  CHECK(t==0.);
}

// --------------------------------------------------------------------------
TEST(TimeHistory, ShowHistory)
{
  auto th = TimeHistory::GetTimeHistory();
  ::do_something();
  th-> TakeSplit("ShowHistory");
  th-> TakeSplit("ShowHistory2");
  th-> ShowHistory("ShowHistory");
  th-> ShowAllHistories();
}

// --------------------------------------------------------------------------
TEST(TimeHistory, ShowClock)
{
  auto th = TimeHistory::GetTimeHistory();
  ::do_something();
  th-> ShowClock("ShowClock:");
}

// --------------------------------------------------------------------------
int main(int argc, char** argv)
{
  MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
  return RUN_ALL_TESTS(argc, argv);
}
