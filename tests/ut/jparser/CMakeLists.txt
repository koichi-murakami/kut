# - add unit tests

# include dir
include_directories(
  ${PROJECT_SOURCE_DIR}/jparser
  ${CPPUTEST_INCLUDE_DIRS})

# lib dir
link_directories(
  ${CMAKE_BINARY_DIR}/jparser
  ${CPPUTEST_LIBRARY_DIRS})

# exec
set (APP_NAMES ut_jparser)

foreach (APP ${APP_NAMES})
  add_executable(${APP} ${APP}.cc)

  target_link_libraries(${APP} jparser ${CPPUTEST_LIBRARIES})

  add_test(${APP} ${APP})
  endforeach()
