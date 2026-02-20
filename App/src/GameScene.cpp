#include "GameScene.h"
#include "Tetris.h"
#include <raylib.h>
#include <string>
#include <format>
#include "Application.h"
#include <iostream>

namespace Tetris
{

	void GameScene::Init()
	{
		

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

		BeginMode2D(m_Camera);
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
		TETRONIMO t = m_Tetris.upcomingTetronimos[(m_Tetris.currentTetronimoIndex + 1) % 3];
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				
				int currentSquare = tetronimos[TETRONIMO_INDEX(t, m_Tetris.currentRotation, x, y)]; // look into cleaning this
				DrawRectangle(x * SQUARE_SIZE + 11.0f * SQUARE_SIZE, y * SQUARE_SIZE + 0.0f * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, m_Tetris.colors[currentSquare]);
				// fix hard coded values
			}
		}

		t = m_Tetris.upcomingTetronimos[(m_Tetris.currentTetronimoIndex + 2) % 3];
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{

				int currentSquare = tetronimos[TETRONIMO_INDEX(t, m_Tetris.currentRotation, x, y)]; // look into cleaning this
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