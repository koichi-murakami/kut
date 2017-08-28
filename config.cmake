#==============================================================================
# CMake configuration for kut
#
# NOTE:
# CACHE variables can be changed in CMake CLI with -D option.
#==============================================================================

set(CMAKE_INSTALL_PREFIX /home/kmura/work/kut/work
    CACHE STRING "Install prefix")

# Optimizaton / Debug flags
set(OPTIMIZE TRUE CACHE BOOL "Optimizaton flag (O3)")
set(DEBUG FALSE CACHE BOOL "Debug mode")

# Development flag (set false for release)
set(DEVMODE FALSE CACHE BOOL "Development mode")

# Optional configurations
# Compiler
#set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_CXX_COMPILER icpc)

# non-default software path
set(CPPUTEST_DIR /opt/cpputest)
