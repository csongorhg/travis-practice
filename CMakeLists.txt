cmake_minimum_required(VERSION 3.7)
project(encode_decode)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)

if(UNIX)
    include(CodeCoverage)
endif()