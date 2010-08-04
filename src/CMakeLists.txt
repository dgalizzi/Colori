#SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
file(GLOB colori_SRC *.cpp)

#set (CMAKE_CXX_FLAGS_DEBUG  ${CMAKE_CXX_FLAGS_DEBUG} -g -O0)
#set (CMAKE_BUILD_TYPE Debug)

add_executable(colori ${colori_SRC})
target_link_libraries(colori sfml-system sfml-window sfml-graphics)
install(TARGETS colori DESTINATION bin)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/bin/" DESTINATION share/colori)

message("Prefix: ${CMAKE_INSTALL_PREFIX}")
CONFIGURE_FILE( ${CMAKE_CURRENT_SOURCE_DIR}/Config.hpp.cmake ${CMAKE_CURRENT_SOURCE_DIR}/Config.hpp )

