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
    application.GetSceneManager().AddSceneToSequence<Tetris::MenuScene>();
    application.GetSceneManager().AddSceneToSequence<Tetris::GameScene>();
    application.GetSceneManager().AddSceneToSequence<Tetris::DeathScene>();


    application.addTexture("Block", "resources/squareTexture.jpg");
    application.GetAssetManager().addShader("Spin", "resources/vsSpin.glsl", "resources/fsBase.glsl");
    application.GetAssetManager().addShader("Trail", "resources/vsBase.glsl", "resources/fsTrail.glsl");
    application.GetAssetManager().addShader("Pulsate", "resources/vsPulsate.glsl", "resources/fsBase.glsl");



    application.GotoScene(0);
    application.Run();
}