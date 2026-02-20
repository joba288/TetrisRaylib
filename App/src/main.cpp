#include <iostream>
#include "Application.h"
#include <raylib.h>
#include <SceneManager.h>
#include "MenuScene.h"
#include "GameScene.h"
#include "DeathScene.h"

int main()
{

    Core::ApplicationSpec appSpec = {"Tetris", 1080, 720};
    Core::Application application(appSpec);
    application.GetSceneManager().PushScene<Tetris::MenuScene>();
    application.GetSceneManager().PushScene<Tetris::GameScene>();
    application.GetSceneManager().PushScene<Tetris::DeathScene>();

    application.GotoScene(1);
    application.Run();
}