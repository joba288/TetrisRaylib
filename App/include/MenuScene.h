#pragma once
#include "SceneManager.h"
#include "UISystem.h"

namespace Tetris {
	class MenuScene : public Core::Scene
	{
	public:
		MenuScene();
		virtual ~MenuScene();
		
		virtual void Init() override;
		virtual void OnRender() override;
		virtual void OnUpdate(float ts) override;
	private:
		Core::UISystem m_UISystem;
		Core::UIComponent m_PlayButton;
		Core::UIComponent m_ExitButton;

	};

}