
project(External)

include(FetchContent)

# where dependencies will be downloaded
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/external)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# wrapper target
add_library(External INTERFACE)

target_link_libraries(External
    INTERFACE raylib
)