#pragma once
#include "SceneManager.h"
#include "Tetris.h"

namespace Tetris {
	class DeathScene : public Core::Scene
	{
	public:
		DeathScene();
		virtual ~DeathScene();

		virtual void Init() override;
		virtual void OnRender() override;
		virtual void OnUpdate(float ts) override;

	private:

	};
}