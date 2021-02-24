# - Find CPPUTest library
#
# It defines:
# CPPUTEST_FOUND               If the CPPUTest is found
# CPPUTEST_INCLUDE_DIRS        PATH to the include directory
# CPPUTEST_LIBRARY_DIRS        path to the libraries directories
# CPPUTEST_LIBRARIES           libraries
#
# CPPUTEST_DIR is used for guessing the installed path.
#

message("-- Detecting CppUTest package")

find_package(PkgConfig QUIET)
pkg_check_modules(PC_CPPUTEST QUIET cpputest)

if(PC_CPPUTEST_FOUND)
  set(CPPUTEST_FOUND 1)
else()
  set(CPPUTEST_FOUND 0)
endif()

# find include path
find_path(CPPUTEST_INCLUDE_DIRS CppUTest/CppUTestConfig.h
          HINTS ${CPPUTEST_DIR}/include
                ${PC_CPPUTEST_INCLUDE_DIRS} /usr/include)
if(CPPUTEST_INCLUDE_DIRS MATCHES "^.*-NOTFOUND")
  set(CPPUTEST_FOUND 0)
endif()

# find library path
find_path(CPPUTEST_LIBRARY_DIRS libCppUTest.a
          HINTS ${CPPUTEST_DIR}/lib64 ${CPPUTEST_DIR}/lib
                ${PC_CPPUTEST_LIBRARY_DIRS}
                /usr/lib64 /usr/lib
                /usr/lib/x86_64-linux-gnu
                /usr/lib/powerpc64le-linux-gnu )
if(CPPUTEST_LIBRARY_DIRS MATCHES "^.*-NOTFOUND")
  set(CPPUTEST_FOUND 0)
endif()

# find library
find_library(CPPUTEST_LIB1 NAMES CppUTest PATHS ${CPPUTEST_LIBRARY_DIRS})
if(CPPUTEST_LIB1 MATCHES "^.*-NOTFOUND")
  set(CPPUTEST_FOUND 0)
endif()

find_library(CPPUTEST_LIB2 NAMES CppUTestExt PATHS ${CPPUTEST_LIBRARY_DIRS})
if(CPPUTEST_LIB2 MATCHES "^.*-NOTFOUND")
  set(CPPUTEST_FOUND 0)
endif()

if (CPPUTEST_FOUND)
  set(CPPUTEST_LIBRARIES stdc++ CppUTest CppUTestExt)
endif()

#
include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(CppUTest DEFAULT_MSG
  CPPUTEST_INCLUDE_DIRS CPPUTEST_LIBRARY_DIRS CPPUTEST_LIBRARIES)

mark_as_advanced(CPPUTEST_INCLUDE_DIRS
  CPPUTEST_LIBRARY_DIRS CPPUTEST_LIBRARIES)

if(CPPUTEST_FOUND)
  message("-- CppUTest version: ${PC_CPPUTEST_VERSION}")
endif()

message("-- Detecting CppUTest package - done")
