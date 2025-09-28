
project(External)

include(FetchContent)
add_library(${PROJECT_NAME} INTERFACE)
FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG 5.5)

set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/External)
FetchContent_MakeAvailable(raylib)


target_link_libraries(${PROJECT_NAME} INTERFACE raylib)