#include "GameScene.h"
#include <raylib.h>

void GameScene::OnRender() { DrawCircleV(Vector2{0}, (float)32, MAROON); }
void GameScene::OnUpdate() {}

GameScene::GameScene() {}
GameScene::~GameScene() {}