/*============================================================================
  Copyright 2017 Koichi Murakami

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

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
Stopwatch::~Stopwatch()
{
}

// --------------------------------------------------------------------------
void Stopwatch::Reset()
{
  start_clock_ = times(&start_time_);
}

// --------------------------------------------------------------------------
inline void Stopwatch::Split()
{
  end_real_time = time(&end_times_)
}

// --------------------------------------------------------------------------
inline const char* Stopwatch::GetClockTime() const
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  return asctime (timeinfo);
}

#define times ostimes


// --------------------------------------------------------------------------
G4double Stopwatch::GetRealElapsed() const
{
  G4double diff=fEndRealTime-fStartRealTime;
  return diff/sysconf(_SC_CLK_TCK);
}


// --------------------------------------------------------------------------
G4double G4Timer::GetSystemElapsed() const
{
  G4double diff=fEndTimes.tms_stime-fStartTimes.tms_stime;
  return diff/sysconf(_SC_CLK_TCK);
}

// --------------------------------------------------------------------------
G4double G4Timer::GetUserElapsed() const
{
  G4double diff=fEndTimes.tms_utime-fStartTimes.tms_utime;
  return diff/sysconf(_SC_CLK_TCK);
}

} // end of namespace
