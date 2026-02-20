#pragma once
#include <array>
#include <Tetronimos.h>
#include <raylib.h>
#include <random>
#include <iostream>
#include <algorithm>
#include <cassert>

// TODO:
//
//  GAMEPLAY
// - Death - lose condition
// - Speeding up of interval - difficulty
// - Clean up code - make code specific to tetris.h rahyhghdgh etc
// - Saving Tetronimos
// - Points
// - Pause Menu
// - Rotate fix bug
// - 
// 
// POLISH
// - Camera
// - Camera Shake
// - Textures
// - Music
// - SFX
// - Shaders
// - Animation
// - trail when quick place
// 
// SYSTEMS
// - AssetManager
// - UI System
// - Change Scenes to work more like layers
// - Shaders
// 
// OPENGL PORT
// FIX CMAKE - MAKE IT BUILD ON ANY SYSTEM



namespace Tetris
{
	constexpr int SQUARE_SIZE = 32;
	constexpr int GRID_WIDTH = 10;
	constexpr int GRID_HEIGHT = 20;

	constexpr int GRID_INDEX(int x, int y) 
	{
		return y * GRID_WIDTH + x;
	}

	constexpr enum TETRONIMO
	{
		IBlock = 1,
		JBlock,
		LBlock,
		OBlock,
		SBlock,
		TBlock,
		ZBlock

	};

	constexpr int TETRONIMO_INDEX(int i, int rotation, int x, int y)
	{
		return (((i - 1) * 4 + rotation) * 16 + (y * 4 + x));
	}

	struct Tetris
	{
		std::array<int, (GRID_WIDTH) * (GRID_HEIGHT)> grid = {0}; 
		Vector2 gridPos = { 0,0 }; // point on screen


		int& gridGetSquare(int x, int y)
		{
			return grid[GRID_INDEX(x, y)];
		}
		// maybe id do getters and setters for this to be safe
		int& gridGetSquare(Vector2 pos){ return grid[GRID_INDEX((int)pos.x, (int)pos.y)]; }


		unsigned int score = 0;

		TETRONIMO currentTetronimo = IBlock;
		int currentRotation = 0;
		Vector2 currentPos = {3, 0};

		std::array<TETRONIMO, 3> upcomingTetronimos = { TETRONIMO(rand() % (7) + 1 ),
														TETRONIMO(rand() % (7) + 1) ,
														TETRONIMO(rand() % (7) + 1) };
		unsigned int currentTetronimoIndex = 0;

		TETRONIMO savedTetronimo = TETRONIMO(0);

		float tickTimer = 0.f;
		float tickInterval = 0.3f;

		std::array<Color, 8> colors = {LIGHTGRAY, SKYBLUE, BLUE, ORANGE, YELLOW, GREEN, PURPLE, RED};


		bool checkCollision(Vector2 pos) // temporary needs cleaning up
		{
			bool coll = false;
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					int currentSquare = tetronimos[((currentTetronimo - 1) * 4 + currentRotation) * 16 + (y * 4 + x)];
					if (currentSquare != 0)
					{
						if (((x + pos.x >= GRID_WIDTH || x + pos.x < 0) || (y + pos.y >= GRID_HEIGHT || y + pos.y < 0)))
						{
							coll = true;
						}
						else
						{
							if ((grid[(y + pos.y) * GRID_WIDTH + (x + pos.x)]) != 0)
							{
								coll = true;
							}
						}
					}
				}
			}

			return coll;
		}

		void placeCurrentTetronimo()
		{
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					int currentSquare = tetronimos[TETRONIMO_INDEX(currentTetronimo, currentRotation, x, y)];
					Vector2 gridPos = { x + currentPos.x, y + currentPos.y };
					if (currentSquare != 0)
					{
						gridGetSquare(gridPos) = currentSquare;
					}
				}
			}

			resolveFullLines();


			currentPos = { 3, 0 };
			currentRotation = 0;

			currentTetronimoIndex = ((currentTetronimoIndex + 1) % 3);				   //   increment index position for the next tetronimo
			currentTetronimo = upcomingTetronimos[currentTetronimoIndex]; //			 set the next tetronimo as current
			upcomingTetronimos[currentTetronimoIndex] = TETRONIMO(rand() % (7) + 1); //	 get new random tetronimo
		

		}

		Vector2 getLandingPosition()
		{
			for (int y = currentPos.y; y < GRID_HEIGHT-1; y++)
			{
				if (checkCollision(Vector2{ currentPos.x, (float)y+1}))
				{
					return Vector2{ currentPos.x, (float)y}; // dangerous
				}
			}

		}




		void resolveFullLines()
		{
			std::vector<int> fullLines;
			fullLines.reserve(4);

			int emptyCount = 0;
			for (int y = 0; y < GRID_HEIGHT; y++)
			{
				emptyCount = 0;
				for (int x = 0; x < GRID_WIDTH; x++)
				{

					int currentSquare = gridGetSquare(x, y);
					if (currentSquare == 0)
					{
						emptyCount++;
					}
				}
				if (emptyCount == 0)
				{
					fullLines.push_back(y);

				}
			}

			// set lines to 0
			for (int i = 0; i < fullLines.size(); i++)
			{
				score++;
				for (int x = 0; x < GRID_WIDTH; x++)
				{
					gridGetSquare(x, fullLines[i]) = 0;
				}
			}
			// move lines down
			//	make new grid and skip over full lines
			std::array<int, (GRID_WIDTH) * (GRID_HEIGHT)> newGrid = { 0 };
			int newGrid_y = GRID_HEIGHT - 1;
			for (int y = GRID_HEIGHT-1; y > 0; y--)
			{
				bool emptyLine = 0;
				for (int i = 0; i < fullLines.size(); i++) { if (y == fullLines[i]) emptyLine = 1; }
				if (!emptyLine) {
					for (int x = 0; x < GRID_WIDTH; x++)
					{
						newGrid[GRID_INDEX(x, newGrid_y)] = gridGetSquare(x, y);


					}
					newGrid_y--;
				}
				
			}
			grid = newGrid; // change this to only be if any empty
		}
	};


	

}