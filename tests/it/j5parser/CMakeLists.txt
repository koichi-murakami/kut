# - build j5parser

# executable
set (APP_NAME j5parser)
add_executable(${APP_NAME} jsonparser.cc main.cc)

install(TARGETS ${APP_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
