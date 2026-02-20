#include "DeathScene.h"
#include <raylib.h>


namespace Tetris {
    DeathScene::DeathScene()
    {
    }

    DeathScene::~DeathScene()
    {
    }

    void DeathScene::Init() {}

    void DeathScene::OnRender()
    {

        int screenWidth = 1080;

        ClearBackground(RAYWHITE);


        // Circle shapes and lines
        DrawCircle(screenWidth / 5, 120, 35, DARKBLUE);
        DrawCircleGradient(screenWidth / 5, 220, 60, GREEN, SKYBLUE);
        DrawCircleLines(screenWidth / 5, 340, 80, DARKBLUE);
        DrawEllipse(screenWidth / 5, 120, 25, 20, YELLOW);
        DrawEllipseLines(screenWidth / 5, 120, 30, 25, YELLOW);

        // Rectangle shapes and lines
        DrawRectangle(screenWidth / 4 * 2 - 60, 100, 120, 60, RED);
        DrawRectangleGradientH(screenWidth / 4 * 2 - 90, 170, 180, 130, MAROON, GOLD);
        DrawRectangleLines(screenWidth / 4 * 2 - 40, 320, 80, 60, ORANGE);  // NOTE: Uses QUADS internally, not lines


    }

    void DeathScene::OnUpdate(float ts)
    {
    }
}