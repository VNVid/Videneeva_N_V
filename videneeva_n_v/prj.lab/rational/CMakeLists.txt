cmake_minimum_required(VERSION 3.13)

project(Rational)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

include_directories("../prj.parts")

add_library(rational rational.cpp rational.h)
add_executable(rational_test  test.cpp)

target_link_libraries(rational_test rational )