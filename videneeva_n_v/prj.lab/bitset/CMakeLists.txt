cmake_minimum_required(VERSION 3.13)

project(bitset)


add_library(bitset bitset.cpp bitset.h)
add_executable(bitset_test  test.cpp)

target_link_libraries(bitset_test bitset)