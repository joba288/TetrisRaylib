#pragma once
#include <array>
#include <Tetronimos.h>
#include <raylib.h>
#include <random>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <string>

#include <RendererAdapter.h> // from Core
#include <ParticleSystem.h>
#include <ParticleSystem.h>

// make it independent to raylib


// TODO:
//
//  GAMEPLAY
// - Death - lose condition
// - Speeding up of interval - difficulty
// - Saving Tetronimos
// - Pause Menu
// 
// POLISH

// - Music
// - SFX
// - Animation
// - trail when quick place
// 
// SYSTEMS
// - UI System
// - Change Scenes to work more like layers
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

	struct ivec2 { int x, y; };

	struct Grid
	{
		ivec2 pos = { 0, 0 };
		std::array<int, (GRID_WIDTH)* (GRID_HEIGHT)> grid = { 0 };
		std::array<float, (GRID_WIDTH* GRID_HEIGHT)> gridDepth = {0.0f};

		int& getSquare(int x, int y) { return grid[GRID_INDEX(x, y)]; }
		float& getDepth(int x, int y) { return gridDepth[GRID_INDEX(x, y)]; }
		int& getSquare(ivec2 pos) { return grid[GRID_INDEX((int)pos.x, (int)pos.y)]; } // getters and setters

		void initDepthGrid()
		{
			for (int i = 0; i < GRID_WIDTH*GRID_HEIGHT; ++i) {
				gridDepth[i] = 0.0f;
			}
		}
	};

	struct Tetris // Change to class
	{

		Grid grid;

		unsigned int score = 0;

		TETRONIMO currentTetronimo = IBlock;
		int currentRotation = 0;
		ivec2 currentPos = {3, 0};
		float currentDepth = 2.0f;
		ivec2 quickPlacePos = {3, 0};

		ivec2 previousPos = { 0, 0 };

		ivec2 trailStart = currentPos;
		int trailEndY = quickPlacePos.y;
		int trailRot = 0;
		TETRONIMO trailTetronimo = currentTetronimo;

		int currentShape; 

		std::array<TETRONIMO, 3> upcomingTetronimos = { TETRONIMO(rand() % (7) + 1 ),
														TETRONIMO(rand() % (7) + 1) ,
														TETRONIMO(rand() % (7) + 1) };
		unsigned int currentTetronimoIndex = 0;

		TETRONIMO savedTetronimo = TETRONIMO(0);

		float tickTimer = 0.f;
		float tickInterval = 0.3f;

		std::array<Color, 8> colors = {LIGHTGRAY, SKYBLUE, BLUE, ORANGE, YELLOW, GREEN, PURPLE, RED};

		Color trailColor = colors[currentTetronimo];

		Vector2 minPos;
		Vector2 maxPos;

		Core::ParticleSystem particleSystem;
		

	
		// INPUT FUNCTIONS

		void onInputRotatePressed()
		{
			int previousRotation = currentRotation;
			currentRotation += 1;
			currentRotation %= 4;
			if (checkCollision(currentPos))
				currentRotation = previousRotation;

			quickPlacePos = getLandingPosition();
		}
		void onInputLeftPressed() 
		{
			if (!checkCollision({ currentPos.x - 1, currentPos.y }))
			{
				currentPos.x -= 1;
				
				quickPlacePos = getLandingPosition();
				
			}
		}
		void onInputRightPressed() 
		{
			if (!checkCollision({ currentPos.x + 1, currentPos.y }))
			{
				currentPos.x += 1;
				
				quickPlacePos = getLandingPosition();

			}
		}
		void onInputSpeedPlacePressed()
		{
			trailStart = currentPos; trailEndY = quickPlacePos.y;
			trailColor = colors[currentTetronimo];
			trailRot = currentRotation;
			trailTetronimo = currentTetronimo;
			currentPos = quickPlacePos;
			
		}
		void onInputSaveTetronimoPressed()
		{
			if (savedTetronimo == 0) // None Saved
			{
				
				savedTetronimo = currentTetronimo;
				initNextTetronimo();
			}
			else                     // Tetronimo Already Saved
			{
				initNextTetronimo(savedTetronimo);
				savedTetronimo = TETRONIMO(0);
			}
		}
		void Tick(float ts) 
		{
			tickTimer += ts;
			if (tickTimer > tickInterval)
			{
				tickTimer = 0.f;
				if (checkCollision({ currentPos.x, currentPos.y + 1 }))
				{
					placeCurrentTetronimo();
				}
				else
				{
					currentPos.y += 1;
					quickPlacePos = getLandingPosition();
				}
			}
		}
		

		// DRAW FUNCTIONS
		void drawGrid(Core::RendererAdapter& r)
		{
			for (int y = 0; y < GRID_HEIGHT; y++)
			{
				for (int x = 0; x < GRID_WIDTH; x++)
				{
					int currentSquare = grid.getSquare(x, y);
					Color c = colors[currentSquare]; // Replace color
					if (currentSquare == 0)
						r.drawRectangle(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, c.r, c.g, c.b, c.a);
					else
						r.drawTexture(x * SQUARE_SIZE, y * SQUARE_SIZE, 1, c.r, c.g, c.b, c.a);
				}
			}
		}
		void drawCurrentTetronimo(Core::RendererAdapter& r)
		{
			// Draws the current tetronimo at its grid position, as well as the place where it will land

			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					int currentSquare = tetronimos[TETRONIMO_INDEX(currentTetronimo, currentRotation, x, y)];

					if (currentSquare != 0)
					{
						Color c = colors[currentSquare];
						r.drawTexture(x * SQUARE_SIZE + currentPos.x * SQUARE_SIZE, y * SQUARE_SIZE + currentPos.y * SQUARE_SIZE,1, c.r, c.g, c.b, c.a);
						r.drawTexture(x * SQUARE_SIZE + quickPlacePos.x * SQUARE_SIZE, y * SQUARE_SIZE + quickPlacePos.y * SQUARE_SIZE,1, c.r, c.g, c.b, 125);					}
				}
			}

		}
		void drawUpcomingTetronimo(Core::RendererAdapter& r, unsigned int i, int posX, int posY, float scale)
		{
			TETRONIMO t = upcomingTetronimos[(currentTetronimoIndex + i) % 3];
			drawGUITetronimo(r, t, posX, posY, scale);
		}
		void drawSavedTetronimo(Core::RendererAdapter& r, int posX, int posY, float scale)
		{
			if (savedTetronimo != 0)
				drawGUITetronimo(r, savedTetronimo, posX, posY, scale);
		}
		void drawGUITetronimo(Core::RendererAdapter& r, TETRONIMO t, int posX, int posY, float scale)
		{
			float sSize = SQUARE_SIZE * scale;

			float baseX = posX * SQUARE_SIZE;
			float baseY = posY * SQUARE_SIZE;

			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					int currentSquare = tetronimos[TETRONIMO_INDEX(t, 1, x, y)];
					Color c = colors[currentSquare];

					float px = baseX + x * sSize;
					float py = baseY + y * sSize;

					if (currentSquare == 0)
					{}
						//r.drawRectangle(px, py, sSize, sSize, c.r, c.g, c.b, c.a);
						
					else
						r.drawTexture(px, py, scale, c.r, c.g, c.b, 255);
				}
			}
		}
		void drawScore(Core::RendererAdapter& r)
		{
			r.drawText(std::to_string(score).c_str(), 20, 10, 80, 0, 0, 0, 255);
		}
		void drawTrail(Core::RendererAdapter& r)
		{
			Color c = trailColor;

			// Find start and end of the tetronimo
			minPos = { 4,4 };
			maxPos = { -1,-1 };

			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					int currentSquare = tetronimos[TETRONIMO_INDEX(trailTetronimo, trailRot, x, y)]; // TODO Cache this somewhere
					if (currentSquare != 0)
					{
						if (x < minPos.x) minPos.x = x;
						if (y < minPos.y) minPos.y = y;
						if (x > maxPos.x) maxPos.x = x;
						if (y > maxPos.y) maxPos.y = y;
					}
				}
			}

			minPos.x += trailStart.x;
			minPos.y += trailStart.y;
			maxPos.x += trailStart.x;
			maxPos.y += trailStart.y;

			r.drawRectangle(
				minPos.x * SQUARE_SIZE,
				minPos.y * SQUARE_SIZE,
				(maxPos.x - minPos.x + 1) * SQUARE_SIZE,
				(trailEndY - minPos.y + 2) * SQUARE_SIZE, c.r, c.g, c.b, c.a);
		}
		//

		void combineGridTetronimoDepth(std::array<float, (GRID_WIDTH*GRID_HEIGHT)>& result)
		{
			result = grid.gridDepth;
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					int currentSquare = tetronimos[TETRONIMO_INDEX(currentTetronimo, currentRotation, x, y)]; // look into cleaning this

					if (currentSquare != 0)
					{
						result[GRID_INDEX(x + currentPos.x, y + currentPos.y)] = currentDepth;


					}

				}
			}

		}



		bool checkCollision(ivec2 pos)
		{
			const int* currentShape = &tetronimos[TETRONIMO_INDEX(currentTetronimo, currentRotation, 0, 0)];

			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					int currentSquare = currentShape[y * 4 + x];
					if (currentSquare == 0) continue;

					if ((unsigned)(x+pos.x) >= GRID_WIDTH || (unsigned)(y+pos.y) >= GRID_HEIGHT)	// Out of Bounds
						return true;

					if (grid.getSquare(x + pos.x, y + pos.y) != 0) 
						return true;
				}
			}

			return false;
		}

		void placeCurrentTetronimo()
		{
			
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					int currentSquare = tetronimos[TETRONIMO_INDEX(currentTetronimo, currentRotation, x, y)];
					ivec2 posInGrid = { x + currentPos.x, y + currentPos.y };
					if (currentSquare != 0)
					{
						grid.getSquare(posInGrid) = currentSquare;
						grid.getDepth(posInGrid.x, posInGrid.y) = currentDepth;
					}
				}
			}

			resolveFullLines();
			initNextTetronimo();


		}

		void initNextTetronimo()
		{
			currentPos = { 3, 0 };
			currentRotation = 0;
			currentDepth = (rand() % 64 + 2) / 2;
			currentTetronimoIndex = ((currentTetronimoIndex + 1) % 3);				   //   increment index position for the next tetronimo
			currentTetronimo = upcomingTetronimos[currentTetronimoIndex]; //				set the next tetronimo as current
			upcomingTetronimos[currentTetronimoIndex] = TETRONIMO(rand() % (7) + 1); //		get new random tetronimo
			quickPlacePos = getLandingPosition();
		}

		void initNextTetronimo(TETRONIMO t)
		{
			currentPos = { 3, 0 };
			currentRotation = 0;
			currentDepth = (rand() % 64 + 2) / 2;
			currentTetronimoIndex = ((currentTetronimoIndex + 1) % 3);				   //   increment index position for the next tetronimo
			currentTetronimo = t; //				set the next tetronimo as current
			upcomingTetronimos[currentTetronimoIndex] = TETRONIMO(rand() % (7) + 1); //		get new random tetronimo
			quickPlacePos = getLandingPosition();
		}

		ivec2 getLandingPosition()
		{
			for (int y = currentPos.y; y < GRID_HEIGHT-1; y++)
			{
				if (checkCollision(ivec2{ currentPos.x, y+1}))
				{
					return ivec2{ currentPos.x, y}; 
				}
			}
			return ivec2{ currentPos.x, (GRID_HEIGHT - 1) };

		}




		void resolveFullLines()
		{
			std::array<bool, GRID_HEIGHT> linesFull{};
			int combo = 0;

			int emptyCount = 0;
			for (int y = 0; y < GRID_HEIGHT; y++)
			{
				emptyCount = 0;
				for (int x = 0; x < GRID_WIDTH; x++)
				{

					int currentSquare = grid.getSquare(x, y);
					if (currentSquare == 0)
					{
						emptyCount++;
						break;
					}
				}
				if (emptyCount == 0)
				{
					linesFull[y] = true;
					combo++;

					for (int x = 0; x < GRID_WIDTH; x++)
					{
						Core::Particle p;
						p.pos = Vector2{ (float)(x + grid.pos.x + 0.5f) * SQUARE_SIZE, float(y + 1 - 0.5f) * SQUARE_SIZE };
						p.velocity = Vector2{ 0, 32 };
						p.sizeStart = Vector2{ SQUARE_SIZE, SQUARE_SIZE };
						//p.sizeEnd = Vector2{ 1, 1 };
						p.sizeEnd = Vector2{SQUARE_SIZE, SQUARE_SIZE};
						p.colorStart = RAYWHITE;
						p.colorEnd = Color{255, 255, 255, 0};
						p.age = 0.0f;
						//p.age = (x) / GRID_WIDTH;
						p.lifetime = 1.0f;
						p.rotationStart = 0.f;
						p.rotationEnd = 0.0f;

						createParticle(p);
					}

				}
				
			}

			score += combo * 4;

			int write_y = GRID_HEIGHT - 1;

			for (int y = GRID_HEIGHT-1; y >= 0; y--)
			{
				if (!linesFull[y]) {
					for (int x = 0; x < GRID_WIDTH; x++)
					{
						grid.getSquare(x, write_y) = grid.getSquare(x, y); // i dont think this needs to be 2 for loops
						grid.getDepth(x, write_y) = grid.getDepth(x, y);



					}
					write_y--;
				}
				
			}
			
			
		}

		 Core::ParticleSystem& getParticleSystem()
		{
			return particleSystem;
		}

		void createParticle(const Core::Particle& p)
		{
			particleSystem.AddParticle(p);
		}
	};


	

}