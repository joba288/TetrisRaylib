#pragma once
#include "SceneManager.h"
#include "Tetris.h"
#include "RaylibRenderer.h"

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
		Shader lightingShader;
		Shader spinShader;

		//Lighting Shader
		int depthGridLoc;
		int screenSizeLoc;
		int lightPosLoc;
		int squareSizeLoc;
		int gridSizeLoc;
		//Spin Shader
		int tLoc;
		int centreLoc;

		float time = 0.f;

		RaylibRenderer renderer;

		int screenWidth;// = Core::Application::Get().GetSpec().ScreenWidth;
		int screenHeight;// = Core::Application::Get().GetSpec().ScreenHeight;
		float screenSize[2];// = { screenWidth, screenHeight };
		int squareSize = SQUARE_SIZE;
		unsigned int gridSize[2] = { GRID_WIDTH, GRID_HEIGHT };

		std::array<float, GRID_WIDTH* GRID_HEIGHT> gridAndCurrentDepth;

	};
}