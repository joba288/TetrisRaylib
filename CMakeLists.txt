# CMakeList.txt : CMake project for TetrisRaylib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.15)

project(TetrisRaylib)

set(CMAKE_CXX_STANDARD 23)

# Debug / Release output folders
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(External)
add_subdirectory(Core)
add_subdirectory(App)



