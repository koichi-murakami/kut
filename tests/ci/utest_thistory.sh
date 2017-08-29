#!/bin/sh -
# ======================================================================
#  Build & run : cuda-devinfo
# ======================================================================
export LANG=C

# ======================================================================
# functions
# ======================================================================
check_error() {
  if [ $? -ne 0 ]; then
    exit -1
  fi
}

show_line() {
echo "========================================================================"
}

# ======================================================================
# main
# ======================================================================
show_line
echo "@@ Run unit tests..."
cd build/tests/ut/thistory
ut_stopwatch -v -ojunit
./ut_timehistory -v -ojunit

exit $?
