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
		//

		Core::Application::Get().GetAssetManager().addShaderFromMemory("Lighting", vsLighting, fsLighting);

		lightingShader = Core::Application::Get().GetAssetManager().getShader("Lighting");
		spinShader = Core::Application::Get().GetAssetManager().getShader("Spin");

		// Locs
		depthGridLoc = GetShaderLocation(lightingShader, "depthGrid");
		screenSizeLoc = GetShaderLocation(lightingShader, "windowSize");
		lightPosLoc = GetShaderLocation(lightingShader, "lightPos");
		squareSizeLoc = GetShaderLocation(lightingShader, "squareSize");
		gridSizeLoc = GetShaderLocation(lightingShader, "gridSize");

		tLoc = GetShaderLocation(spinShader, "t");
		centreLoc = GetShaderLocation(spinShader, "centre");

		renderer.LoadTexture("Block");

		m_Camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
		m_Camera.target = { (float)m_Tetris.grid.pos.x + (GRID_WIDTH * SQUARE_SIZE) / 2, (float)m_Tetris.grid.pos.y + (GRID_HEIGHT * SQUARE_SIZE) / 2 };
		m_Camera.rotation = 0.0f;
		m_Camera.zoom = 1.0f;

		screenWidth = Core::Application::Get().GetSpec().ScreenWidth;
		screenHeight = Core::Application::Get().GetSpec().ScreenHeight;
		screenSize[0] = screenWidth; screenSize[1] = screenHeight;
	}

	
	void GameScene::OnRender()
	{
		ClearBackground(RAYWHITE);

		float mouseUV[2] = { GetMouseX(), GetMouseY() };		

		SetShaderValueV(lightingShader, depthGridLoc, gridAndCurrentDepth.data(), SHADER_UNIFORM_FLOAT, GRID_WIDTH * GRID_HEIGHT);
		SetShaderValue(lightingShader, screenSizeLoc, &screenSize, SHADER_UNIFORM_VEC2);
		SetShaderValue(lightingShader, lightPosLoc, &mouseUV, SHADER_UNIFORM_VEC2);
		SetShaderValue(lightingShader, squareSizeLoc, &squareSize, SHADER_UNIFORM_INT);
		SetShaderValue(lightingShader, gridSizeLoc, &gridSize, SHADER_UNIFORM_IVEC2);
		SetShaderValue(spinShader, tLoc, &time, SHADER_UNIFORM_FLOAT);
		

		//BeginMode2D(m_Camera);
		BeginShaderMode(lightingShader);
			m_Tetris.drawGrid(renderer);
			m_Tetris.drawCurrentTetronimo(renderer);
		EndShaderMode();

		BeginShaderMode(spinShader);
			Vector2 upcomingTPos1 = { 332 + (4 * 16), (4 * 16) };
			SetShaderValue(spinShader, centreLoc, &upcomingTPos1, SHADER_UNIFORM_VEC2);
			m_Tetris.drawUpcomingTetronimo(renderer, 1, 11, 0, 1);
		EndShaderMode();

		m_Tetris.drawUpcomingTetronimo(renderer, 2, 32, 0, 0.5);
		m_Tetris.drawSavedTetronimo(renderer, 11, 11, 1);
		
		
		// TODO: MAKE THIS TAKE POSITIONS
		
		//EndMode2D();
		//GUI
		m_Tetris.drawScore(renderer);

	}
	void GameScene::OnUpdate(float ts)
	{

		time += ts;
		m_Tetris.Tick(ts);
		

		if (IsKeyPressed(KEY_UP))
			m_Tetris.onInputRotatePressed();
			m_Tetris.combineGridTetronimoDepth(gridAndCurrentDepth);

		if (IsKeyPressed(KEY_RIGHT))
			m_Tetris.onInputRightPressed();
			m_Tetris.combineGridTetronimoDepth(gridAndCurrentDepth);
		
		if (IsKeyPressed(KEY_LEFT))
			m_Tetris.onInputLeftPressed();
			m_Tetris.combineGridTetronimoDepth(gridAndCurrentDepth);

		if (IsKeyPressed(KEY_DOWN))
			m_Tetris.onInputSpeedPlacePressed();
			m_Tetris.combineGridTetronimoDepth(gridAndCurrentDepth);
		if (IsKeyPressed(KEY_SPACE))
			m_Tetris.onInputSaveTetronimoPressed();
			m_Tetris.combineGridTetronimoDepth(gridAndCurrentDepth);

		
	}

	GameScene::GameScene() {}
	GameScene::~GameScene() {}

}