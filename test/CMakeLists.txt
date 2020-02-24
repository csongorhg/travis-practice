cmake_minimum_required(VERSION 3.7)

include(Qt)
include(Catch)

file(GLOB TEST_SOURCES encoder_test.cpp)

add_executable(unit unit.cpp ${TEST_SOURCES})
target_link_libraries(unit Qt5::Core)