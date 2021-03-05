/*============================================================================
  Copyright 2017-2021 Koichi Murakami

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file LICENSE for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef JPARSER_VERSION_H_
#define JPARSER_VERSION_H_

#define JPARSER_VERSION_MAJOR "2"
#define JPARSER_VERSION_MINOR "0.0"
#define JPARSER_VERSION_BUILD 0x01cf237

namespace {
  const int build_head = (JPARSER_VERSION_BUILD & 0xffff000) >> 12;
  const int build_tail = JPARSER_VERSION_BUILD & 0xfff;
} // namespace

#endif
