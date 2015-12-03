# - Top-level CMakeLists.txt for KUT

cmake_minimum_required(VERSION 3.4)

#------------------------------------------------------------------------------
project(KUT)
#------------------------------------------------------------------------------
# installation prefixes for libraries
set(CMAKE_INSTALL_PREFIX $ENV{HOME}/Library/kut)
set(CPPUTEST_DIR /opt/cpputest)

# compiler selection
set(CMAKE_CXX_COMPILER g++)
#set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_CXX_COMPILER icpc)

# debug mode
set(DEBUG FALSE CACHE BOOL "Debug Mode")

#------------------------------------------------------------------------------
# Do not edit below
#------------------------------------------------------------------------------
# cmake modules
set(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/cmake/Modules
    ${CMAKE_MODULE_PATH})

# find packages
find_package(CppUTest REQUIRED)

#------------------------------------------------------------------------------
# c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# build options
if(NOT CMAKE_BUILD_TYPE)
  if(DEBUG)
    set(CMAKE_BUILD_TYPE "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
  else()
    set(CMAKE_BUILD_TYPE "RelWithDebInfo")
  endif()
endif()

# library path
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

# include path
if(NOT DEFINED CMAKE_INSTALL_INCDIR)
  set(CMAKE_INSTALL_INCDIR "include")
endif()

#------------------------------------------------------------------------------
# parameters for building
message(STATUS "--------------------------------------------------------")
message(STATUS "Parameters for building")

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")

message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CppUTest_FOUND: ${CPPUTEST_FOUND}")
message(STATUS "CPPUTEST_INCLUDE_DIRS: ${CPPUTEST_INCLUDE_DIRS}")
message(STATUS "CPPUTEST_LIBRARIES: ${CPPUTEST_INCLUDE_DIRS}")
message(STATUS "--------------------------------------------------------")

#------------------------------------------------------------------------------
# add subdiretories...
#include(CTest)
#enable_testing()

# adding sub directories to the project
# libraries
add_subdirectory(json5_parser)
#add_subdirectory(timer)

#add_subdirectory(tests/ut)
# unit testing

# integration testing
#add_subdirectory(testing/it)

# binaries (after `make install')
#add_subdirectory(xxx EXCLUDE_FROM_ALL)
