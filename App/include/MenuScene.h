#pragma once
#include "SceneManager.h"

namespace Tetris {
	class MenuScene : public Core::Scene
	{
	public:
		MenuScene();
		virtual ~MenuScene();
		
		virtual void Init() override;
		virtual void OnRender() override;
		virtual void OnUpdate() override;


	};

}