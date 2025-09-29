# CMakeList.txt : CMake project for TetrisRaylib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

project(TetrisRaylib)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(App)
add_subdirectory(Core)
add_subdirectory(External)



