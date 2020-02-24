cmake_minimum_required(VERSION 3.7)

include(Qt)
include(Catch)

file(GLOB SOURCES *.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(encode_decode ${SOURCES})
target_link_libraries(encode_decode Qt5::Core)