/*============================================================================
  Copyright 2017-2021 Koichi Murakami

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file License for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "stopwatch.h"

namespace kut {

// --------------------------------------------------------------------------
Stopwatch::Stopwatch()
{
  Reset();
}

// --------------------------------------------------------------------------
void Stopwatch::Reset()
{
  times(&start_time_);
  start_clock_ = g_clock::now();
}

// --------------------------------------------------------------------------
void Stopwatch::Split()
{
  times(&end_time_);
  end_clock_ = g_clock::now();
}

// --------------------------------------------------------------------------
double Stopwatch::GetRealElapsed() const
{
  std::chrono::nanoseconds diff = end_clock_ - start_clock_;
  double sec = diff.count() / 1.e9;
  return sec;
}

// --------------------------------------------------------------------------
double Stopwatch::GetSystemElapsed() const
{
  double diff = end_time_.tms_stime - start_time_.tms_stime;
  return diff / sysconf(_SC_CLK_TCK);
}

// --------------------------------------------------------------------------
double Stopwatch::GetUserElapsed() const
{
  double diff = end_time_.tms_utime - start_time_.tms_utime;
  return diff / sysconf(_SC_CLK_TCK);
}

// --------------------------------------------------------------------------
std::string Stopwatch::GetClockTime() const
{
  g_clock::time_point now = g_clock::now();

  time_t t = g_clock::to_time_t(now);

  char buf[26];

#ifdef _MSC_VER
  ctime_s(buf, 26, &t);
#else
  ctime_r(&t, buf);
#endif

  return std::string(buf);
}

} // end of namespace
