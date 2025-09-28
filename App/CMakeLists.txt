project(App)

add_executable(App src/main.cpp)
target_include_directories(App PRIVATE include)
target_link_libraries(App PRIVATE Core)