/*============================================================================
  CUGEANT4 - CUDA Geant4 Project
  Copyright 2012 [[@copyright]]

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "gtimer.h"

namespace kut {
// --------------------------------------------------------------------------
GTimer& GTimer::GetGTimer()
{
  static GTimer the_timer;
  return the_timer;
}

// --------------------------------------------------------------------------
GTimer::GTimer()
  : g4timer_(), t0_(0.)
{
  split_history_.clear();

  g4timer_.Start();
  g4timer_.Stop();
  t0_ = g4timer_.GetUserElapsed() + g4timer_.GetSystemElapsed();
}

// --------------------------------------------------------------------------
GTimer::~GTimer()
{
}

// --------------------------------------------------------------------------
void GTimer::TakeSplitTime(const std::string& key)
{
  g4timer_.Stop();
  double split = g4timer_.GetUserElapsed() + g4timer_.GetSystemElapsed();
  split_history_[key] = split - t0_;
}

// --------------------------------------------------------------------------
bool GTimer::FindAKey(const std::string& key) const
{
  std::map<std::string, double>::const_iterator itr;
  itr = split_history_.find(key);
  if ( itr != split_history_.end() ) return true;
  else return false;
}

// --------------------------------------------------------------------------
double GTimer::GetTime(const std::string& key) const
{
  std::map<std::string, double>::const_iterator itr;
  itr = split_history_.find(key);
  if ( itr != split_history_.end() ) {
    return itr-> second;
  } else {
    std::cout << "[WARNING] G4TImer::GetTime() cannot find a key. "
              << key << std::endl;
    return 0.;
  }
}

// --------------------------------------------------------------------------
void GTimer::ShowHistory(const std::string& key) const
{
  std::map<std::string, double>::const_iterator itr;
  itr = split_history_.find(key);
  if ( itr != split_history_.end() ) {
    std::cout << "[" << itr-> first << "] : "
              << itr-> second << "s" << std::endl;
  } else {
    std::cout << "[WARNING] G4TImer::ShowHistory() cannot find a key. "
              << key << std::endl;
  }
}

// --------------------------------------------------------------------------
void GTimer::ShowAllHistories() const
{
  std::multimap<double, std::string> histories_by_time;
  std::map<std::string, double>::const_iterator itr;
  for ( itr = split_history_.begin(); itr != split_history_.end(); ++itr) {
    histories_by_time.insert(std::make_pair(itr->second, itr->first));
  }

  std::cout << std::endl << "* All timer histories" << std::endl;

  std::map<double, std::string>::const_iterator itr2;
  for ( itr2 = histories_by_time.begin();
        itr2 != histories_by_time.end();  ++itr2) {
    std::cout << "[" << itr2-> second << "] : "
              << itr2-> first << "s" << std::endl;
  }

  std::cout << std::endl;
}

// --------------------------------------------------------------------------
void GTimer::ShowClock(const std::string& prefix) const
{
  std::cout << prefix << " " << g4timer_.GetClockTime() << std::endl;
}

} // end of namespace
