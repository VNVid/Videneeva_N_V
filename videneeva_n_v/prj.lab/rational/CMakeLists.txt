cmake_minimum_required(VERSION 3.13)

project(Rational)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

add_executable(test rational.cpp rational.h test.cpp)