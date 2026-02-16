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
		
		m_Camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f } ;
		m_Camera.target = {m_Tetris.gridPos.x + (GRID_WIDTH*SQUARE_SIZE)/2, m_Tetris.gridPos.y + (GRID_HEIGHT*SQUARE_SIZE)/2};
		m_Camera.rotation = 0.0f;
		m_Camera.zoom = 1.0f;
		//

		BeginMode2D(m_Camera);
		// Draw Grid
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{

				int currentSquare = (m_Tetris.grid[y * GRID_WIDTH + x]);
				DrawRectangle(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, m_Tetris.colors[currentSquare]);
			}
		}

		// Draw Current Tetronimo
		Vector2 landingPos = m_Tetris.getLandingPosition();
		

		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				int currentSquare = tetronimos[((m_Tetris.currentTetronimo-1) * 4 + m_Tetris.currentRotation) * 16 + (y * 4 + x)]; // look into cleaning this

				if (currentSquare != 0)
				{
					DrawRectangle(x * SQUARE_SIZE + m_Tetris.currentPos.x * SQUARE_SIZE, y * SQUARE_SIZE + m_Tetris.currentPos.y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, m_Tetris.colors[currentSquare]);
					Color c = m_Tetris.colors[currentSquare];
					DrawRectangle(x * SQUARE_SIZE + landingPos.x * SQUARE_SIZE, y * SQUARE_SIZE + landingPos.y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, Color{c.r, c.g, c.b, 125});
					
				}

				



			}
		}

		EndMode2D();

		//GUI



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