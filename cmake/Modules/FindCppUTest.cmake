# - Find CPPUTest library
# It defines:
# CPPUTEST_FOUND               If the CPPUTest is found
# CPPUTEST_INCLUDE_DIRS        PATH to the include directory
# CPPUTEST_LIBRARIES           libraries

find_package(PkgConfig)

pkg_check_modules(PC_CPPUTEST cpputest>=3.7)

find_path(CPPUTEST_INCLUDE_DIR CppUTest/CppUTestConfig.h
  HINTS ${PC_CPPUTEST_INCLUDEDIR} ${PC_CPPUTEST_INCLUDE_DIRS}
)

find_library(CPPUTEST_LIBRARY NAMES CppUTest libCppUTest
  HINTS ${PC_CPPUTEST_LIBDIR} ${PC_CPPUTEST_LIBRARY_DIRS}
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(CppUTest DEFAULT_MSG
  CPPUTEST_LIBRARY CPPUTEST_INCLUDE_DIR)

mark_as_advanced(CPPUTEST_INCLUDE_DIR CPPUTEST_LIBRARY)
