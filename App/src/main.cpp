#include <iostream>
#include "Application.h"
#include <raylib.h>
#include <SceneManager.h>
#include "MenuScene.h"
#include "GameScene.h"


int main(void)
{
    Core::ApplicationSpec appSpec = {"Tetris", 1080, 720};
    Core::Application application(appSpec);

    application.GetSceneManager().PushScene<MenuScene>();
    application.GetSceneManager().PushScene<GameScene>();
    

    application.Run();

    

}