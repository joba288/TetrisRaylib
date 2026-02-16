#pragma once
#include "SceneManager.h"
#include "Tetris.h"

namespace Tetris {
	class GameScene : public Core::Scene
	{
	public:
		GameScene();
		virtual ~GameScene();

		virtual void Init() override;
		virtual void OnRender() override;
		virtual void OnUpdate(float ts) override;

	private:
		Tetris m_Tetris;
		Camera2D m_Camera = { 0 };
	};
}