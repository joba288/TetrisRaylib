#include "DeathScene.h"
#include <raylib.h>
#include <Application.h>
#include <UISystem.h>


namespace Tetris {
    DeathScene::DeathScene()
    {
    }

    DeathScene::~DeathScene()
    {
    }

    void DeathScene::Init() 
    {
        int screenWidth = Core::Application::Get().GetSpec().ScreenWidth;
        m_PlayButton.SetData(Core::UIComponentData{ screenWidth / 2, 300, 200, 100, 0, true, "Play Again", 20, WHITE, BLACK, GRAY });
        m_ExitButton.SetData(Core::UIComponentData{ screenWidth / 2, 500, 200, 100, 0, true, "Exit", 20, WHITE, BLACK, GRAY });

        m_UISystem.AddComponent("Title", Core::UIComponentData{ screenWidth / 2, 0, 200, 100, 0, true, "You Died", 50, BLACK, Color{0,0,0,0}, Color{0,0,0,0} });
        m_UISystem.AddComponent("Resume Button", m_PlayButton);
        m_UISystem.AddComponent("Exit Button", m_ExitButton);
    }

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
        m_UISystem.OnUpdate(ts);

        if (m_PlayButton.IsClicked())
            Core::Application::Get().GetSceneManager().PreviousScene();
        if (m_ExitButton.IsClicked())
            Core::Application::Get().Stop();
    }
}