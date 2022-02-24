cmake_minimum_required(VERSION 3.13)

project(m3i)


add_library(m3i m3i.cpp m3i.h)
add_executable(m3i_test  test.cpp)

target_link_libraries(m3i_test m3i )