# - add testint

# include dir
include_directories(
  ${PROJECT_SOURCE_DIR}/jparser
  ${GTEST_INCLUDE_DIRS}
)

# lib dir
link_directories(
  ${PROJECT_BINARY_DIR}/jparser
)

# exec
set (APP_NAMES ut_jparser)

foreach (APP ${APP_NAMES})
  add_executable(${APP} ${APP}.cc)

  target_link_libraries(
    ${APP}
    jparser
    ${GTEST_BOTH_LIBRARIES}
  )

  set_target_properties(
    ${APP}
    PROPERTIES INSTALL_RPATH
    ${PROJECT_BINARY_DIR}/jparser
    BUILD_WITH_INSTALL_RPATH TRUE
  )

#  gtest_add_tests(${APP} "" ${APP}.cc)
endforeach()
