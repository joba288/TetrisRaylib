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
        m_UISystem.AddComponent("Exit Button", m_ExitButton); // TODO Unload on scene change
    }

    void DeathScene::OnRender()
    {

        ClearBackground(RAYWHITE);

        m_UISystem.Draw();


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