#
#  CMakeLists.txt for buidlig kut
#
#  Copyright 2017 Koichi Murakami
#
#  ***************************
#  !! DONOT EDIT THIS FILE  !!
#  ***************************
#
cmake_minimum_required(VERSION 3.2)
include(config.cmake)
#==============================================================================
project(kut)
#==============================================================================

# version.h generation (true for release)
if(DEVMODE)
  set(SKIP_VERSION FALSE)
else()
  set(SKIP_VERSION TRUE)
endif()

# cmake modules
set(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/cmake/Modules
    ${CMAKE_MODULE_PATH})

# library path (lib or lib64)
if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
  set(_LIBDIR_DEFAULT "lib")
  if(CMAKE_SYSTEM_NAME MATCHES "Linux"
      AND NOT EXISTS "/etc/debian_version")
    if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
      set(_LIBDIR_DEFAULT "lib64")
    endif()
  endif()
  set(CMAKE_INSTALL_LIBDIR "${_LIBDIR_DEFAULT}")
endif()

# find packages
find_package(CppUTest QUIET)

# c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# build options
if(NOT CMAKE_BUILD_TYPE)
  if(DEBUG)
    set(CMAKE_BUILD_TYPE "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
  elseif(OPTIMIZE)
    set(CMAKE_BUILD_TYPE "Release")
  else()
    set(CMAKE_BUILD_TYPE "RelWithDebInfo")
  endif()
endif()

#------------------------------------------------------------------------------
# parameters for building
message(STATUS "--------------------------------------------------------")
message(STATUS "Parameters for building")
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CPPUTEST_FOUND: ${CPPUTEST_FOUND}")
message(STATUS "--------------------------------------------------------")

#------------------------------------------------------------------------------
# version.h (#.##d# + rev# / dev flag d/a/b/rc)
if(NOT SKIP_VERSION)
set(KUT_VERSION_MAJOR 1)
set(KUT_VERSION_MINOR 2.0)

execute_process (COMMAND git rev-parse --short HEAD OUTPUT_VARIABLE
                KUT_VERSION_BUILD OUTPUT_STRIP_TRAILING_WHITESPACE)

configure_file(
  "${PROJECT_SOURCE_DIR}/cmake/jparser_version.h.in"
  "${PROJECT_SOURCE_DIR}/jparser/version.h"
)
configure_file(
  "${PROJECT_SOURCE_DIR}/cmake/thistory_version.h.in"
  "${PROJECT_SOURCE_DIR}/thistory/version.h"
)
endif()

#------------------------------------------------------------------------------
# adding sub directories to the project
add_subdirectory(jparser)
add_subdirectory(thistory)

if (CPPUTEST_FOUND)
include(CTest)
enable_testing()

# unit testing
add_subdirectory(tests/ut)
endif()

# integration testing
add_subdirectory(tests/it)
