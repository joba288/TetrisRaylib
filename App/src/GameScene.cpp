#include "GameScene.h"
#include "Tetris.h"
#include <raylib.h>
#include <string>
#include <format>
#include "Application.h"
#include <iostream>
#include <array>

namespace Tetris
{



	void GameScene::Init()
	{
		for (int i = 0; i < 200; ++i) {
			m_Tetris.gridDepth[i] = 0.0f;
		}


	}

	void GameScene::OnRender()
	{

		int screenWidth = Core::Application::Get().GetSpec().ScreenWidth;
		int screenHeight = Core::Application::Get().GetSpec().ScreenHeight;

		ClearBackground(RAYWHITE);

		// Temp

		m_Camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
		m_Camera.target = { m_Tetris.gridPos.x + (GRID_WIDTH * SQUARE_SIZE) / 2, m_Tetris.gridPos.y + (GRID_HEIGHT * SQUARE_SIZE) / 2 };
		m_Camera.rotation = 0.0f;
		m_Camera.zoom = 1.0f;


		//
		std::array<float, GRID_WIDTH* GRID_HEIGHT> gridAndCurrentDepth;
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				gridAndCurrentDepth[GRID_INDEX(x,y)] = m_Tetris.gridDepth[GRID_INDEX(x, y)];
			}
		}

		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				int currentSquare = tetronimos[TETRONIMO_INDEX(m_Tetris.currentTetronimo, m_Tetris.currentRotation, x, y)]; // look into cleaning this

				if (currentSquare != 0)
				{
					gridAndCurrentDepth[GRID_INDEX(x + m_Tetris.currentPos.x, y + m_Tetris.currentPos.y)] = m_Tetris.currentDepth;


				}

			}
		}





		int depthGridLoc = GetShaderLocation(lightingShader, "depthGrid");
		SetShaderValueV(lightingShader, depthGridLoc, &gridAndCurrentDepth, SHADER_UNIFORM_FLOAT, 200);
		int screenSizeLoc = GetShaderLocation(lightingShader, "windowSize");
		float screenSize[2] = { screenWidth, screenHeight };
		SetShaderValue(lightingShader, screenSizeLoc, &screenSize, SHADER_UNIFORM_VEC2);

		int lightPosLoc = GetShaderLocation(lightingShader, "lightPos");
		float mouseUV[2] = {GetMouseX()-screenWidth/2.0, GetMouseY()};
		SetShaderValue(lightingShader, lightPosLoc, &mouseUV, SHADER_UNIFORM_VEC2);

		int squareSizeLoc = GetShaderLocation(lightingShader, "squareSize");
		int squareSize = 32;
		SetShaderValue(lightingShader, squareSizeLoc, &squareSize, SHADER_UNIFORM_INT);

		int gridSizeLoc = GetShaderLocation(lightingShader, "gridSize");
		unsigned int gridSize[2] = {GRID_WIDTH, GRID_HEIGHT};
		SetShaderValue(lightingShader, gridSizeLoc, &gridSize, SHADER_UNIFORM_IVEC2);

		BeginMode2D(m_Camera);

		BeginShaderMode(lightingShader);

		// Draw Grid
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{

				int currentSquare = m_Tetris.gridGetSquare(x, y);
				DrawRectangle(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, m_Tetris.colors[currentSquare]);
			}
		}// need function draw tetronimo, draw grid
		
		// Draw Current Tetronimo
		Vector2 landingPos = m_Tetris.getLandingPosition();

		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				int currentSquare = tetronimos[TETRONIMO_INDEX(m_Tetris.currentTetronimo, m_Tetris.currentRotation, x, y)]; // look into cleaning this

				if (currentSquare != 0)
				{
					DrawRectangle(x * SQUARE_SIZE + m_Tetris.currentPos.x * SQUARE_SIZE, y * SQUARE_SIZE + m_Tetris.currentPos.y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, m_Tetris.colors[currentSquare]);
					Color c = m_Tetris.colors[currentSquare];
					DrawRectangle(x * SQUARE_SIZE + landingPos.x * SQUARE_SIZE, y * SQUARE_SIZE + landingPos.y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, Color{ c.r, c.g, c.b, 125 });

				}





			}
		}

		EndShaderMode();


		TETRONIMO t = m_Tetris.upcomingTetronimos[(m_Tetris.currentTetronimoIndex + 1) % 3];
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				
				int currentSquare = tetronimos[TETRONIMO_INDEX(t, 1, x, y)]; // look into cleaning this
				DrawRectangle(x * SQUARE_SIZE + 11.0f * SQUARE_SIZE, y * SQUARE_SIZE + 0.0f * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, m_Tetris.colors[currentSquare]);
				// fix hard coded values
			}
		}

		t = m_Tetris.upcomingTetronimos[(m_Tetris.currentTetronimoIndex + 2) % 3];
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{

				int currentSquare = tetronimos[TETRONIMO_INDEX(t, 1, x, y)]; // look into cleaning this
				DrawRectangle(x * SQUARE_SIZE/2 + 32.0f * SQUARE_SIZE/2, y * SQUARE_SIZE/2 + 0.0f * SQUARE_SIZE/2, SQUARE_SIZE/2, SQUARE_SIZE/2, m_Tetris.colors[currentSquare]);
				// fix hard coded values
			}
		}
		
		EndMode2D();

		//GUI
		DrawText(std::to_string(m_Tetris.score).c_str(), 20, 10, 80, BLACK);


	}
	void GameScene::OnUpdate(float ts)
	{
		m_Tetris.tickTimer += ts;

		if (IsKeyPressed(KEY_UP))
		{
			m_Tetris.currentRotation += 1;
			m_Tetris.currentRotation %= 4;

		}

		if (IsKeyPressed(KEY_RIGHT))
		{
			if (!m_Tetris.checkCollision({ m_Tetris.currentPos.x + 1, m_Tetris.currentPos.y }))
			{
				m_Tetris.currentPos.x += 1;
			}
		}

		if (IsKeyPressed(KEY_LEFT))
		{
			if (!m_Tetris.checkCollision({ m_Tetris.currentPos.x - 1, m_Tetris.currentPos.y }))
			{
				m_Tetris.currentPos.x -= 1;
			}
		}

		if (IsKeyPressed(KEY_DOWN))
		{
			m_Tetris.currentPos = m_Tetris.getLandingPosition();
		}

		if (m_Tetris.tickTimer > m_Tetris.tickInterval)
		{
			m_Tetris.tickTimer = 0.f;
			if (m_Tetris.checkCollision({ m_Tetris.currentPos.x, m_Tetris.currentPos.y + 1 }))
			{
				m_Tetris.placeCurrentTetronimo();
			}
			else
			{
				m_Tetris.currentPos.y += 1;
			}
		}
	}

	GameScene::GameScene() {}
	GameScene::~GameScene() {}

}