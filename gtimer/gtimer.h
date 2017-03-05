/*============================================================================
  CUGEANT4 - CUDA Geant4 Project
  Copyright 2012 [[@copyright]]

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef GTIMER_H_
#define GTIMER_H_

#include <map>
#include <string>
#include "G4Timer.hh"

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

namespace kut {

class GTimer {
public:
  static GTimer& GetGTimer();
  ~GTimer();

  /// take split
  void TakeSplitTime(const std::string& key);

  /// find a specified event key
  bool FindAKey(const std::string& key) const;

  /// get time of a specified event key
  double GetTime(const std::string& key) const;

  /// show history of a specified event key
  void ShowHistory(const std::string& key) const;

  /// show all histories
  void ShowAllHistories() const;

  /// show current time
  void ShowClock(const std::string& prefix="") const;

private:
  GTimer();
  DISALLOW_COPY_AND_ASSIGN(GTimer);

  /// G4Timer
  G4Timer g4timer_;

  /// Time = 0
  double t0_;

  /// split history
  std::map<std::string, double> split_history_;

};

} // end of namespace

#endif
