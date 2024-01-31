cmake_minimum_required(VERSION 3.28.1)
project(locator LANGUAGES CXX)

set(CORES 6)
set(MAKEFLAGS "-j${CORES}" CACHE STRING "" FORCE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(config.json ${CMAKE_CURRENT_BINARY_DIR}/server/config.json COPYONLY)
configure_file(config.json ${CMAKE_CURRENT_BINARY_DIR}/client/config.json COPYONLY)

add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(proto)