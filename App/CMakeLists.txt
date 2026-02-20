project(App)

add_executable(App src/main.cpp "include/MenuScene.h" "src/MenuScene.cpp" "include/GameScene.h" "src/GameScene.cpp" "include/Tetris.h" "include/Tetronimos.h" "include/DeathScene.h" "src/DeathScene.cpp")
target_include_directories(App PRIVATE include)
target_link_libraries(App PRIVATE Core)