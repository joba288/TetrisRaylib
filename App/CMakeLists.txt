project(App)

add_executable(App src/main.cpp "include/MenuScene.h" "src/MenuScene.cpp" "include/GameScene.h" "src/GameScene.cpp" "include/Tetris.h" "include/Tetronimos.h" "include/DeathScene.h" "src/DeathScene.cpp" "src/RaylibRenderer.cpp"  "include/PauseScene.h" "src/PauseScene.cpp")
target_include_directories(App PRIVATE include)
target_link_libraries(App PRIVATE Core)

set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/resources)

add_custom_command(TARGET App POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${RESOURCES_DIR}
    $<TARGET_FILE_DIR:App>/resources
)