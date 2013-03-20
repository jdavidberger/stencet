cmake_minimum_required (VERSION 2.6) 
project (stencet) 

SET(stencet_VERSION_MAJOR 0.0)

EXEC_PROGRAM(hg ARGS tip OUTPUT_VARIABLE hg_tip)
SET(stencet_minor_version "unknown")
STRING(REGEX REPLACE "changeset:[ \t]*([0-9]+):(.*)" "\\1" stencet_VERSION_MINOR "${hg_tip}")
FILE(WRITE ${CMAKE_BINARY_DIR}/VERSION "v${stencet_VERSION_MAJOR}.${stencet_VERSION_MINOR}")
FILE(READ ${CMAKE_BINARY_DIR}/VERSION stencet_version)
message("Building ${stencet_version}")

set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/third)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} -std=c++11 -Wno-reorder -O0")

include_directories(include)

add_subdirectory(src)
#add_subdirectory(Doxygen)

install(DIRECTORY include/stencet DESTINATION include)
