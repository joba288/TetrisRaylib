project(Core)

add_library(Core STATIC "include/Application.h" "src/Application.cpp" "include/SceneManager.h" "src/SceneManager.cpp" "include/RendererAdapter.h" "include/AssetManager.h" "src/AssetManager.cpp" "include/ParticleSystem.h" "src/ParticleSystem.cpp" "include/UISystem.h" "src/UISystem.cpp" )
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_link_libraries(Core PUBLIC External)