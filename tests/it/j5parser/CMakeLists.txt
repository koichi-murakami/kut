# - build j5parser

# executable
set (APP_NAME jparser)

include_directories(${PROJECT_SOURCE_DIR}/json_parser)
link_directories(${CMAKE_BINARY_DIR}/json_parser)

add_executable(${APP_NAME} main.cc)
target_link_libraries(${APP_NAME} json_parser)

install(TARGETS ${APP_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
