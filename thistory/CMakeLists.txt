# - build thistory library

# library
add_library(
  thistory SHARED
  stopwatch.cc
  timehistory.cc
)
# headers
set(HEADERS
  stopwatch.h
  timehistory.h
)

# install
install(TARGETS thistory LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCDIR})
