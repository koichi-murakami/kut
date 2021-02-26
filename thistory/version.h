/*============================================================================
  Copyright 2017 Koichi Murakami

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file LICENSE for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef THISTORY_VERSION_H_
#define THISTORY_VERSION_H_

#define THISTORY_VERSION_MAJOR "2"
#define THISTORY_VERSION_MINOR "0.0"
#define THISTORY_VERSION_BUILD 0xc0fc43d

namespace {
  const int build_head = (THISTORY_VERSION_BUILD & 0xffff000) >> 12;
  const int build_tail = THISTORY_VERSION_BUILD & 0xfff;
} // namespace

#endif
