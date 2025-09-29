#pragma once
#include "SceneManager.h"


class GameScene : public Core::Scene
{
public:
	GameScene();
	virtual ~GameScene();

	virtual void OnRender() override;
	virtual void OnUpdate() override;


};