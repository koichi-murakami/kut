/*============================================================================
  Copyright 2017 Koichi Murakami

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include <iostream>
#include "timehistory.h"

namespace kut {
// --------------------------------------------------------------------------
TimeHistory* TimeHistory::GetTimeHistory()
{
  static TimeHistory thistory;
  return &thistory;
}

// --------------------------------------------------------------------------
TimeHistory::TimeHistory()
  : sw_(), t0_(0.)
{
  split_history_.clear();

  sw_.Split();
  t0_ = sw_.GetUserElapsed() + sw_.GetSystemElapsed();
}

// --------------------------------------------------------------------------
TimeHistory::~TimeHistory()
{
}

// --------------------------------------------------------------------------
void TimeHistory::TakeSplit(const std::string& key)
{
  sw_.Split();
  double split = sw_.GetUserElapsed() + sw_.GetSystemElapsed();
  split_history_[key] = split - t0_;
}

// --------------------------------------------------------------------------
bool TimeHistory::FindAKey(const std::string& key) const
{
  std::map<std::string, double>::const_iterator itr;
  itr = split_history_.find(key);
  if ( itr != split_history_.end() ) return true;
  else return false;
}

// --------------------------------------------------------------------------
double TimeHistory::GetTime(const std::string& key) const
{
  std::map<std::string, double>::const_iterator itr;
  itr = split_history_.find(key);
  if ( itr != split_history_.end() ) {
    return itr-> second;
  } else {
    std::cout << "[WARNING] TimeHistory::GetTime() cannot find a key. "
              << key << std::endl;
    return 0.;
  }
}

// --------------------------------------------------------------------------
void TimeHistory::ShowHistory(const std::string& key) const
{
  std::map<std::string, double>::const_iterator itr;
  itr = split_history_.find(key);
  if ( itr != split_history_.end() ) {
    std::cout << "[" << itr-> first << "] : "
              << itr-> second << "s" << std::endl;
  } else {
    std::cout << "[WARNING] TimeHistory::ShowHistory() cannot find a key. "
              << key << std::endl;
  }
}

// --------------------------------------------------------------------------
void TimeHistory::ShowAllHistories() const
{
  std::multimap<double, std::string> histories_by_time;
  std::map<std::string, double>::const_iterator itr;
  for ( itr = split_history_.begin(); itr != split_history_.end(); ++itr) {
    histories_by_time.insert(std::make_pair(itr->second, itr->first));
  }

  std::cout << std::endl << "* All time histories" << std::endl;

  std::map<double, std::string>::const_iterator itr2;
  for ( itr2 = histories_by_time.begin();
        itr2 != histories_by_time.end();  ++itr2) {
    std::cout << "[" << itr2-> second << "] : "
              << itr2-> first << "s" << std::endl;
  }

  std::cout << std::endl;
}

// --------------------------------------------------------------------------
void TimeHistory::ShowClock(const std::string& prefix) const
{
  std::cout << prefix << " " << sw_.GetClockTime() << std::endl;
}

} // end of namespace