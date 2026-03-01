#pragma once
#include "SceneManager.h"
#include "Tetris.h"
#include "RaylibRenderer.h"
#include "ParticleSystem.h"

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
		Core::ParticleSystem particleSystem;
		Camera2D m_Camera = { 0 };
		Shader lightingShader;
		Shader spinShader;
		Shader trailShader;

		//Lighting Shader
		int depthGridLoc;
		int screenSizeLoc;
		int lightPosLoc;
		int squareSizeLoc;
		int gridSizeLoc;
		//Spin Shader
		int tLoc;
		int centreLoc;
		//Trail Shader
		int trail_StartLoc;
		int trail_gridHeightLoc;
		int trail_screenSizeLoc;
		int trail_squareSizeLoc;
		int trail_currentTimeLoc;
		int trail_timePlacedLoc;

		float time = 0.f;
		float timePlaced = 0.f;

		RaylibRenderer renderer;

		int screenWidth;// = Core::Application::Get().GetSpec().ScreenWidth;
		int screenHeight;// = Core::Application::Get().GetSpec().ScreenHeight;
		float screenSize[2];// = { screenWidth, screenHeight };
		int squareSize = SQUARE_SIZE;
		unsigned int gridSize[2] = { GRID_WIDTH, GRID_HEIGHT };

		std::array<float, GRID_WIDTH* GRID_HEIGHT> gridAndCurrentDepth;

	};
}