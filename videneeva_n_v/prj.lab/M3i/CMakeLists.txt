cmake_minimum_required(VERSION 3.13)

project(M3i)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

include_directories("../prj.parts")

add_library(M3i M3i.cpp M3i.h)
add_executable(M3i_test  test.cpp)

target_link_libraries(M3i_test M3i )