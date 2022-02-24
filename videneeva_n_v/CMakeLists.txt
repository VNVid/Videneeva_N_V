cmake_minimum_required(VERSION 3.13)

project(videneeva_n_v)

add_subdirectory(prj.codeforces)
add_subdirectory(prj.lab)

include_directories(prj.thirdparty prj.lab)