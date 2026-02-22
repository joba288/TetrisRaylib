project(Core)

add_library(Core STATIC "include/Application.h" "src/Application.cpp" "include/SceneManager.h" "src/SceneManager.cpp" "include/RendererAdapter.h" "../App/include/RaylibRenderer.h"   )
target_include_directories(Core PUBLIC include)

target_link_libraries(Core PUBLIC External)