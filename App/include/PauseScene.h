#pragma once
#include "SceneManager.h"
#include <UISystem.h>

namespace Tetris {
	class PauseScene : public Core::Scene
	{
	public:
		PauseScene();
		virtual ~PauseScene();

		virtual void Init() override;
		virtual void OnRender() override;
		virtual void OnUpdate(float ts) override;

	private:
		Core::UISystem m_UISystem;
		Core::UIComponent m_ResumeButton;
		Core::UIComponent m_ExitButton;
	};

}