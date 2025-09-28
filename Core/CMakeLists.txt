project(Core)

add_library(Core STATIC src/foo.cpp "include/Application.h" "src/Application.cpp")
target_include_directories(Core PUBLIC include)

target_link_libraries(Core PUBLIC External)