# - build gtimer library

# library
add_library(
  gtimer SHARED
  gtimer.cc timer.cc
)
# headers
set(HEADERS
  gtimer.h
  timer.h
)

# install
install(TARGETS gtimer LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCDIR})
