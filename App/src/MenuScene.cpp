#include "MenuScene.h"
#include <raylib.h>
#include <Application.h>
#include <UISystem.h>


namespace Tetris {
    MenuScene::MenuScene()
    {
    }

    MenuScene::~MenuScene()
    {
    }

    void MenuScene::Init() 
    {
        int screenWidth = Core::Application::Get().GetSpec().ScreenWidth;

        m_PlayButton.SetData(Core::UIComponentData{ screenWidth / 2, 300, 200, 100, 0, true, "Play", 20, WHITE, BLACK, GRAY });
        m_ExitButton.SetData(Core::UIComponentData{ screenWidth / 2, 500, 200, 100, 0, true, "Exit", 20, WHITE, BLACK, GRAY });

        m_UISystem.AddComponent("Title", Core::UIComponentData{ screenWidth / 2, 0, 200, 100, 0, true, "Tetris", 50, BLACK, Color{0,0,0,0}, Color{0,0,0,0} });
        m_UISystem.AddComponent("Resume Button", m_PlayButton);
        m_UISystem.AddComponent("Exit Button", m_ExitButton);
    }

    void MenuScene::OnRender()
    {

        int screenWidth = Core::Application::Get().GetSpec().ScreenWidth;

        ClearBackground(RAYWHITE);
        m_UISystem.Draw();

        // Circle shapes and lines
        DrawCircle(screenWidth / 2, 120, 35, DARKBLUE);
        DrawCircleGradient(screenWidth / 2, 220, 60, GREEN, SKYBLUE);
        DrawCircleLines(screenWidth / 2, 340, 80, DARKBLUE);
        DrawEllipse(screenWidth / 2, 120, 25, 20, YELLOW);
        DrawEllipseLines(screenWidth / 2, 120, 30, 25, YELLOW);


    }

    void MenuScene::OnUpdate(float ts)
    {
        m_UISystem.OnUpdate(ts);

        if (m_PlayButton.IsClicked())
            Core::Application::Get().GetSceneManager().NextScene();
        if (m_ExitButton.IsClicked())
            Core::Application::Get().Stop();
    }
}