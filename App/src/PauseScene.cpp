#include "PauseScene.h"
#include <raylib.h>
#include <Application.h>


namespace Tetris {
    PauseScene::PauseScene()
    {
    }

    PauseScene::~PauseScene()
    {
    }

    void PauseScene::Init()
    {
        int screenWidth = Core::Application::Get().GetSpec().ScreenWidth;

        m_ResumeButton.SetData(Core::UIComponentData{ screenWidth / 2, 300, 200, 100, 0, true, "Resume", 20, WHITE, BLACK, GRAY });
        m_ExitButton.SetData(Core::UIComponentData{ screenWidth / 2, 500, 200, 100, 0, true, "Exit", 20, WHITE, BLACK, GRAY });

        m_UISystem.AddComponent("Title", Core::UIComponentData{ screenWidth / 2, 0, 200, 100, 0, true, "PAUSED", 50, BLACK, Color{0,0,0,0}, Color{0,0,0,0} });
        m_UISystem.AddComponent("Resume Button", m_ResumeButton);
        m_UISystem.AddComponent("Exit Button", m_ExitButton);
    }
    void PauseScene::OnRender()
    {
        int screenWidth = Core::Application::Get().GetSpec().ScreenWidth;
        int screenHeight = Core::Application::Get().GetSpec().ScreenHeight;
        

        //ClearBackground(RAYWHITE);
        //ClearBackground(Color{255, 255, 255, 50});
        DrawRectangle(0, 0, screenHeight, screenHeight, Color{255, 255,255,50});
        m_UISystem.Draw();



    }

    void PauseScene::OnUpdate(float ts)
    {
        m_UISystem.OnUpdate(ts);

        if (m_ExitButton.IsClicked())
            Core::Application::Get().GetSceneManager().PreviousScene();
        
        if (IsKeyPressed(KEY_P) || m_ResumeButton.IsClicked()) 
            Core::Application::Get().GetSceneManager().PopScene();
    }
}