# - build j5parser

# executable
set (APP_NAME j5parser)

include_directories(${PROJECT_SOURCE_DIR}/jparser)
link_directories(${CMAKE_BINARY_DIR}/jparser)

add_executable(${APP_NAME} main.cc)
target_link_libraries(${APP_NAME} jparser)

file(COPY sample.json5 DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY test.json5 DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS ${APP_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
