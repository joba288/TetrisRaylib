#include "GameScene.h"
#include "Tetris.h"
#include <raylib.h>
#include <string>
#include <format>

namespace Tetris
{

	void GameScene::Init()
	{
		

	}

	void GameScene::OnRender()
	{
		
		ClearBackground(RAYWHITE);

		
		// Draw Grid
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				switch (m_Tetris.grid[y * GRID_WIDTH + x])
				{
				case 0:
					DrawRectangle(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, LIGHTGRAY);
					break;
				case 1:
					DrawRectangle(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, RED);
					DrawRectangleLines(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, BLACK);
					break;

				
				};
			}
		}

		// Draw Current Tetronimo
		m_Tetris.currentRotation = 0;

		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				int currentSquare = tetronimos[(m_Tetris.currentTetronimo * 4 + m_Tetris.currentRotation) * 16 + (y * 4 + x)];

				if (currentSquare == 1)
				{
					DrawRectangle(x * SQUARE_SIZE + m_Tetris.currentPos.x * SQUARE_SIZE, y * SQUARE_SIZE + m_Tetris.currentPos.y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, RED);
					DrawRectangleLines(x * SQUARE_SIZE + m_Tetris.currentPos.x * SQUARE_SIZE, y * SQUARE_SIZE + m_Tetris.currentPos.y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, BLACK);;
				}
			}
		}





	}
	void GameScene::OnUpdate()
	{

	}

	GameScene::GameScene() {}
	GameScene::~GameScene() {}

}