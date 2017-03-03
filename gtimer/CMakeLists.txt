# - build json_parser library

# library
add_library(
  jparser SHARED
  jsonparser.cc
)
# headers
set(HEADERS
  jsonparser.h
  picojson.h
)

# install
install(TARGETS jparser LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCDIR})
