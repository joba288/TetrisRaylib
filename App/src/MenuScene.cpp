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

        m_UISystem.AddComponent("Title", Core::UIComponentData{ screenWidth / 2, 0, 200, 100, 0, true, "Tetris", 50, WHITE, Color{0,0,0,0}, Color{0,0,0,0} });
        m_UISystem.AddComponent("Resume Button", m_PlayButton);
        m_UISystem.AddComponent("Exit Button", m_ExitButton);
    }

    void MenuScene::OnRender()
    {

        int screenWidth = Core::Application::Get().GetSpec().ScreenWidth;

        ClearBackground(Color{ 62, 59,101,255 });
        m_UISystem.Draw();


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