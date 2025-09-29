#pragma once
#include "SceneManager.h"


class MenuScene : public Core::Scene
{
	public:
		MenuScene();
		virtual ~MenuScene();

		virtual void OnRender() override;
		virtual void OnUpdate() override;


};