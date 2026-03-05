#include "GameScene.h"
#include "Tetris.h"
#include <raylib.h>
#include <string>
#include <format>
#include "Application.h"
#include <iostream>
#include <algorithm>
#include <array>
#include <ParticleSystem.h>
#include <PauseScene.h>

namespace Tetris
{

	

	void GameScene::Init()
	{

		m_Tetris = Tetris();
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
		trailShader = Core::Application::Get().GetAssetManager().getShader("Trail");
		pulsateShader = Core::Application::Get().GetAssetManager().getShader("Pulsate");

		// Locs
		depthGridLoc = GetShaderLocation(lightingShader, "depthGrid");
		screenSizeLoc = GetShaderLocation(lightingShader, "windowSize");
		lightPosLoc = GetShaderLocation(lightingShader, "lightPos");
		squareSizeLoc = GetShaderLocation(lightingShader, "squareSize");
		gridSizeLoc = GetShaderLocation(lightingShader, "gridSize");

		tLoc = GetShaderLocation(spinShader, "t");
		centreLoc = GetShaderLocation(spinShader, "centre");

		trail_StartLoc = GetShaderLocation(trailShader, "trailStart");
		trail_gridHeightLoc = GetShaderLocation(trailShader, "gridHeight");
		trail_screenSizeLoc = GetShaderLocation(trailShader, "windowSize");
		trail_squareSizeLoc = GetShaderLocation(trailShader, "squareSize");
		trail_currentTimeLoc = GetShaderLocation(trailShader, "currentTime");
		trail_timePlacedLoc = GetShaderLocation(trailShader, "timePlaced");

		SetShaderValue(trailShader, trail_gridHeightLoc, &GRID_HEIGHT, SHADER_UNIFORM_INT);
		SetShaderValue(trailShader, trail_screenSizeLoc, &screenSize, SHADER_UNIFORM_VEC2);
		SetShaderValue(trailShader, trail_squareSizeLoc, &SQUARE_SIZE, SHADER_UNIFORM_INT);

		pulsate_timeLoc = GetShaderLocation(pulsateShader, "t");
		pulsate_centreLoc = GetShaderLocation(pulsateShader, "centre");

		renderer.LoadTexture("Block");

		screenWidth = Core::Application::Get().GetSpec().ScreenWidth;
		screenHeight = Core::Application::Get().GetSpec().ScreenHeight;
		screenSize[0] = screenWidth; screenSize[1] = screenHeight;

		m_Camera.offset = { (float)screenWidth / 2.f, (float)screenHeight / 2.f };
		m_BaseCamOffset = m_Camera.offset;
		m_Camera.target = { (float)m_Tetris.grid.pos.x + (GRID_WIDTH * SQUARE_SIZE) / 2
							, (float)m_Tetris.grid.pos.y + (GRID_HEIGHT * SQUARE_SIZE) / 2 };
		m_Camera.rotation = 0.0f;
		m_Camera.zoom = 1.0f;

	}

	
	void GameScene::OnRender()
	{
		ClearBackground(DARKGRAY);

		float mouseUV[2] = { GetMouseX(), GetMouseY() };		

		SetShaderValueV(lightingShader, depthGridLoc, gridAndCurrentDepth.data(), SHADER_UNIFORM_FLOAT, GRID_WIDTH * GRID_HEIGHT);
		SetShaderValue(lightingShader, screenSizeLoc, &screenSize, SHADER_UNIFORM_VEC2);
		SetShaderValue(lightingShader, lightPosLoc, &mouseUV, SHADER_UNIFORM_VEC2);
		SetShaderValue(lightingShader, squareSizeLoc, &squareSize, SHADER_UNIFORM_INT);
		SetShaderValue(lightingShader, gridSizeLoc, &gridSize, SHADER_UNIFORM_IVEC2);
		SetShaderValue(spinShader, tLoc, &time, SHADER_UNIFORM_FLOAT);
		SetShaderValue(pulsateShader, pulsate_timeLoc, &time, SHADER_UNIFORM_FLOAT);
		


		BeginMode2D(m_Camera);

		BeginShaderMode(lightingShader);
			m_Tetris.drawGrid(renderer);
		EndShaderMode();

		

		BeginShaderMode(lightingShader);
			m_Tetris.drawCurrentTetronimo(renderer);
		EndShaderMode();

		SetShaderValue(trailShader, trail_StartLoc, &m_Tetris.trailStart.y, SHADER_UNIFORM_INT);


		SetShaderValue(trailShader, trail_currentTimeLoc, &time, SHADER_UNIFORM_FLOAT);
		SetShaderValue(trailShader, trail_timePlacedLoc, &timePlaced, SHADER_UNIFORM_FLOAT);

		BeginShaderMode(trailShader);
			m_Tetris.drawTrail(renderer);
		EndShaderMode();

		BeginShaderMode(spinShader);

		float scale = .75f;

		Vector2 pos = {
			11 * SQUARE_SIZE,
			1 * SQUARE_SIZE
		};

		float blockSize = SQUARE_SIZE * scale;

		Vector2 centre = {
			pos.x + blockSize * 2.0f,
			pos.y + blockSize * 2.0f
		};

		SetShaderValue(spinShader, centreLoc, &centre, SHADER_UNIFORM_VEC2);
		

		m_Tetris.drawUpcomingTetronimo(
			renderer,
			1,
			pos.x / SQUARE_SIZE,
			pos.y / SQUARE_SIZE,
			scale
		);

		
		EndShaderMode();
		m_Tetris.getParticleSystem().DrawParticles();

		BeginShaderMode(spinShader);
		scale = .75f;

		pos = {
			11 * SQUARE_SIZE,
			5 * SQUARE_SIZE
		};
		

		blockSize = SQUARE_SIZE * scale;
		centre = {
			pos.x + blockSize * 2.0f,
			pos.y + blockSize * 2.0f
		};

		SetShaderValue(spinShader, centreLoc, &centre, SHADER_UNIFORM_VEC2);
		m_Tetris.drawUpcomingTetronimo(
			renderer,
			2,
			pos.x / SQUARE_SIZE,
			pos.y / SQUARE_SIZE,
			scale
		);
		EndShaderMode();



		BeginShaderMode(pulsateShader);
		scale = .75f;

		pos = {
			-4 * SQUARE_SIZE,
			17 * SQUARE_SIZE
		};


		blockSize = SQUARE_SIZE * scale;
		centre = {
			pos.x + blockSize * 2.0f,
			pos.y + blockSize * 2.0f
		};
		SetShaderValue(pulsateShader, pulsate_centreLoc, &centre, SHADER_UNIFORM_VEC2);
		m_Tetris.drawSavedTetronimo(renderer, pos.x/SQUARE_SIZE, pos.y/SQUARE_SIZE, scale);
		EndShaderMode();
		

		
		EndMode2D();

		 
		
		//GUI
		m_Tetris.drawScore(renderer);
		//DrawText(std::to_string(m_ShakeTime).c_str(), 100, 100, 64, BLACK);
		m_UISystem.Draw();


	}
	void GameScene::OnUpdate(float ts)
	{
		m_Tetris.getParticleSystem().OnUpdate(ts);
		m_UISystem.OnUpdate(ts);

		time += ts;
		m_Tetris.Tick(ts);
		m_Tetris.combineGridTetronimoDepth(gridAndCurrentDepth);

		shakeCamera(ts);

		if (m_Tetris.gameOver)
			Core::Application::Get().GetSceneManager().NextScene();

		if (IsKeyPressed(KEY_UP))
		{
			m_Tetris.onInputRotatePressed();
			/*m_Tetris.combineGridTetronimoDepth(gridAndCurrentDepth);*/
		}
		if (IsKeyPressed(KEY_RIGHT))
		{
			m_Tetris.onInputRightPressed();
			/*m_Tetris.combineGridTetronimoDepth(gridAndCurrentDepth);*/
		}
		if (IsKeyPressed(KEY_LEFT))
		{
			m_Tetris.onInputLeftPressed();
			/*m_Tetris.combineGridTetronimoDepth(gridAndCurrentDepth);*/
	}
		if (IsKeyPressed(KEY_DOWN))
		{
			Core::Application::Get().PushAlarm(Core::Alarm([this]() {
				setCameraShake(2,0.25f);
				timePlaced = time;
			}, 0.03f));


			m_Tetris.onInputSpeedPlacePressed();
			/*m_Tetris.combineGridTetronimoDepth(gridAndCurrentDepth);*/
			
				

		}
		if (IsKeyPressed(KEY_SPACE))
		{
			m_Tetris.onInputSaveTetronimoPressed();
			/*m_Tetris.combineGridTetronimoDepth(gridAndCurrentDepth);*/
		}

		if (IsKeyPressed(KEY_P))
			Core::Application::Get().GetSceneManager().PushScene<PauseScene>();
		
	}

	void GameScene::setCameraShake(float intensity, float duration)
	{
		m_ShakeIntensity = intensity;
		m_ShakeTime = duration;
	}

	void GameScene::shakeCamera(float ts)
	{
		if (m_ShakeIntensity > 0.0)
			m_Screenshake = { (rand() % int(m_ShakeIntensity) - m_ShakeIntensity / 2) ,
						      (rand() % int(m_ShakeIntensity) - m_ShakeIntensity / 2) };

		m_ShakeTime -= ts;
		if (m_ShakeTime <= 0.0f)
		{
			m_ShakeTime = 0.0f;
			m_Screenshake = { 0.0f };
		}

		m_Camera.offset.x = m_BaseCamOffset.x + m_Screenshake.x;
		m_Camera.offset.y = m_BaseCamOffset.y + m_Screenshake.y;

	}

	GameScene::GameScene() {}
	GameScene::~GameScene() {}

}