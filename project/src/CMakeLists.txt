cmake_minimum_required(VERSION 3.13)

project(maz)

add_library(maze3d maze.cpp maze.h)
add_executable(maze_test test.cpp)

target_link_libraries(maze_test maze3d)