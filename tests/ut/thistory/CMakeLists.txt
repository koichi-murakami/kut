# - add unit tests

# include dir
include_directories(
  ${PROJECT_SOURCE_DIR}/thistory
  ${CPPUTEST_INCLUDE_DIRS})

# lib dir
link_directories(
  ${CMAKE_BINARY_DIR}/thistory
  ${CPPUTEST_LIBRARY_DIRS})

# exec
set (APP_NAMES ut_stopwatch ut_timehistory)

foreach (APP ${APP_NAMES})
  add_executable(${APP} ${APP}.cc)

  target_link_libraries(${APP} thistory ${CPPUTEST_LIBRARIES})

  add_test(${APP} ${APP})
  endforeach()
