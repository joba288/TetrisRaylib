#include "GameScene.h"
#include "Tetris.h"
#include <raylib.h>
#include <string>
#include <format>
#include "Application.h"
#include <iostream>
#include <algorithm>
#include <array>

namespace Tetris
{



	void GameScene::Init()
	{
		m_Tetris.grid.initDepthGrid(); 

		// INJECT SHADER HEADER
		char* vsRaw = LoadFileText("resources/vsLighting.glsl");
		char* fsRaw = LoadFileText("resources/fsLighting.glsl");

		if (!vsRaw || !fsRaw)
		{
			printf("Failed to load shader files\n");
			return;
		}

		std::string vsLighting = vsRaw;
		std::string fsLighting = fsRaw;

		size_t pos = fsLighting.find('\n');
		fsLighting.insert(pos + 1,
			"#define GRID_WIDTH " + std::to_string(GRID_WIDTH) + "\n" +
			"#define GRID_HEIGHT " + std::to_string(GRID_HEIGHT) + "\n");

		UnloadFileText(vsRaw);
		UnloadFileText(fsRaw);

		lightingShader = LoadShaderFromMemory(vsLighting.c_str(), fsLighting.c_str());


	}

	void GameScene::OnRender()
	{

		int screenWidth = Core::Application::Get().GetSpec().ScreenWidth;
		int screenHeight = Core::Application::Get().GetSpec().ScreenHeight;

		ClearBackground(RAYWHITE);

		// Temp

		m_Camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
		m_Camera.target = { (float)m_Tetris.grid.pos.x + (GRID_WIDTH * SQUARE_SIZE) / 2, (float)m_Tetris.grid.pos.y + (GRID_HEIGHT * SQUARE_SIZE) / 2 };
		m_Camera.rotation = 0.0f;
		m_Camera.zoom = 1.0f;

		// TODO Cleanup shader setup
#pragma region Shader Uniform Setup
		std::array<float, GRID_WIDTH* GRID_HEIGHT> gridAndCurrentDepth;
		m_Tetris.combineGridTetronimoDepth(gridAndCurrentDepth);
		int depthGridLoc = GetShaderLocation(lightingShader, "depthGrid");
		SetShaderValueV(lightingShader, depthGridLoc, &gridAndCurrentDepth, SHADER_UNIFORM_FLOAT, GRID_WIDTH*GRID_HEIGHT);
		int screenSizeLoc = GetShaderLocation(lightingShader, "windowSize");
		float screenSize[2] = { screenWidth, screenHeight };
		SetShaderValue(lightingShader, screenSizeLoc, &screenSize, SHADER_UNIFORM_VEC2);
		int lightPosLoc = GetShaderLocation(lightingShader, "lightPos");
		float mouseUV[2] = {GetMouseX()-screenWidth/2.0, GetMouseY()};
		SetShaderValue(lightingShader, lightPosLoc, &mouseUV, SHADER_UNIFORM_VEC2);
		int squareSizeLoc = GetShaderLocation(lightingShader, "squareSize");
		int squareSize = SQUARE_SIZE;
		SetShaderValue(lightingShader, squareSizeLoc, &squareSize, SHADER_UNIFORM_INT);
		int gridSizeLoc = GetShaderLocation(lightingShader, "gridSize");
		unsigned int gridSize[2] = {GRID_WIDTH, GRID_HEIGHT};
		SetShaderValue(lightingShader, gridSizeLoc, &gridSize, SHADER_UNIFORM_IVEC2);
#pragma endregion

		BeginMode2D(m_Camera);
		BeginShaderMode(lightingShader);

		m_Tetris.drawGrid(renderer);
		m_Tetris.drawCurrentTetronimo(renderer);
		EndShaderMode();
		m_Tetris.drawUpcomingTetronimo(renderer, 1, 11, 0, 1);
		m_Tetris.drawUpcomingTetronimo(renderer, 2, 32, 0, 0.5);
		// TODO: MAKE THIS TAKE POSITIONS
		EndMode2D();
		//GUI
		m_Tetris.drawScore(renderer);

	}
	void GameScene::OnUpdate(float ts)
	{

		m_Tetris.Tick(ts);

		if (IsKeyPressed(KEY_UP))
			m_Tetris.onInputRotatePressed();

		if (IsKeyPressed(KEY_RIGHT))
			m_Tetris.onInputRightPressed();
		
		if (IsKeyPressed(KEY_LEFT))
			m_Tetris.onInputLeftPressed();

		if (IsKeyPressed(KEY_DOWN))
			m_Tetris.onInputSpeedPlacePressed();

		
	}

	GameScene::GameScene() {}
	GameScene::~GameScene() {}

}