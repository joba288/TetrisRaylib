#include <iostream>
#include "Application.h"
#include <raylib.h>
#include <SceneManager.h>
#include "MenuScene.h"
#include "GameScene.h"


int main()
{

    Core::ApplicationSpec appSpec = {"Tetris", 1080, 720};
    Core::Application application(appSpec);
    application.GetSceneManager().PushScene<Tetris::MenuScene>();
    application.GetSceneManager().PushScene<Tetris::GameScene>();

    application.GetSceneManager().GotoScene(1);
    
    application.Run();
}