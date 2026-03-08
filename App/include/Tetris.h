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
#include <Application.h>
#include <raymath.h>
#include <iostream>


// make it independent to raylib


// TODO:
//
//  GAMEPLAY
// - Speeding up of interval - difficulty
// - Saving Tetronimos Fix
// 
// POLISH

// - Music
// - SFX
// - Animation
// - trail when quick place



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
		bool gameOver = false;
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

		int stretchHeight = 1;
		int stretchWidth = 1;
		bool placing = false;
		bool moving = false;
		bool alarmOngoing = false;
		


		

		int currentShape; 

		std::array<TETRONIMO, 3> upcomingTetronimos = { TETRONIMO(rand() % (7) + 1 ),
														TETRONIMO(rand() % (7) + 1) ,
														TETRONIMO(rand() % (7) + 1) };
		unsigned int currentTetronimoIndex = 0;

		TETRONIMO savedTetronimo = TETRONIMO(0);

		float tickTimer = 0.f;
		float tickInterval = 0.3f;

	

		std::array<Color, 8> colors = { Color{ 56, 89,179,255}, // DARKBLUE
										Color { 54,197,244,255},// SKYBLUE
										Color { 51,136,222,255},// BLUE
										Color {233,133, 55,255},//ORANGE
										GOLD,// YELLOW
										Color {157,230, 78,255}, // LIME
										Color {204,153,255,255}, // VIOLET
										Color {236, 39, 63,255} }; // RED

		Color trailColor = colors[currentTetronimo];

		Vector2 minPos;
		Vector2 maxPos;

		Core::ParticleSystem particleSystem;
		std::shared_ptr<Core::Alarm> placeAlarm;
		std::shared_ptr<Core::Alarm> moveAlarm;
	
		// INPUT FUNCTIONS

		void onInputRotatePressed()
		{
			if (!moving && !alarmOngoing)
			{

				int previousRotation = currentRotation;
				currentRotation += 1;
				currentRotation %= 4;
				if (checkCollision(currentPos))
					currentRotation = previousRotation;

				quickPlacePos = getLandingPosition();
			}
		}
		void onInputLeftPressed() 
		{
			if (!moving && !alarmOngoing)
			{
				if (!checkCollision({ currentPos.x - 1, currentPos.y }))
				{
					moving = true;
					moveAlarm = Core::Application::Get().PushAlarm(Core::Alarm([this]()
					{
						currentPos.x -= 1;
						quickPlacePos = getLandingPosition();
						moving = false;
					}, 0.045f));

				}
			}
		}
		void onInputRightPressed() 
		{
			if (!moving && !alarmOngoing)
			{
				if (!checkCollision({ currentPos.x + 1, currentPos.y }))
				{
					moving = true;
					moveAlarm = Core::Application::Get().PushAlarm(Core::Alarm([this]()
					{
						currentPos.x += 1;
						quickPlacePos = getLandingPosition();
						moving = false;
					}, 0.045f));

				}
			}
		}

		void onInputSpeedPlacePressed()
		{
			if (!moving && !alarmOngoing)
			{
				moving = true;


				placeAlarm = Core::Application::Get().PushAlarm(Core::Alarm([this]()
				{
					trailStart = currentPos; trailEndY = quickPlacePos.y;
					trailColor = colors[currentTetronimo];
					trailRot = currentRotation;
					trailTetronimo = currentTetronimo;
					currentPos = quickPlacePos;
					placeCurrentTetronimo();




					moving = false;
				}, 0.03f
				));
			}
			
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
			if (!moving && !alarmOngoing)
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
						r.drawRectangle(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, 0.0f, c.r, c.g, c.b, c.a);
					else
						r.drawTexture(x * SQUARE_SIZE, y * SQUARE_SIZE, 1,0, c.r, c.g, c.b, c.a);
				}
			}
		}
		void drawCurrentTetronimo(Core::RendererAdapter& r)
		{
			// Draws the current tetronimo at its grid position, as well as the place where it will land

			
			// width and height of one square in tetronimo
			float w = 1; float h = 1;
			
			minPos = { 4,4 };
			maxPos = { -1,-1 };

			calculateTetronimoMinMax(minPos, maxPos, currentTetronimo, currentRotation);
			
			int tetronimoWidth = maxPos.x - minPos.x + 1;
			int tetronimoHeight = maxPos.y - minPos.y + 1;

			if (moving && moveAlarm && tetronimoWidth > 0)
			{
				float targetWidth = 1.05f; 

				float t = moveAlarm->age / moveAlarm->duration;
				t = Clamp(t, 0.0f, 1.0f);
				t = 1.0f - powf(1.0f - t, 3.0f);

				h = Lerp(1.0f, targetWidth, t);
				w = Lerp(1.0f, targetWidth, t);
			}
			
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					int currentSquare = tetronimos[TETRONIMO_INDEX(currentTetronimo, currentRotation, x, y)];

					if (currentSquare != 0)
					{
						float piecePixelWidth = tetronimoWidth * SQUARE_SIZE;
						float piecePixelHeight = tetronimoHeight * SQUARE_SIZE;

						float baseX = (currentPos.x + minPos.x) * SQUARE_SIZE;
						float baseY = (currentPos.y + minPos.y) * SQUARE_SIZE;

						float centerX = baseX + piecePixelWidth * 0.5f;
						float centerY = baseY + piecePixelHeight * 0.5f;

						float localX = (x - minPos.x) * SQUARE_SIZE;
						float localY = (y - minPos.y) * SQUARE_SIZE;

						float scaledX = localX * w;
						float scaledY = localY * h;

						float drawX = centerX + scaledX - (piecePixelWidth * w) * 0.5f;
						float drawY = centerY + scaledY - (piecePixelHeight * h) * 0.5f;

						Color c = colors[currentTetronimo];
						r.drawTexture(drawX,
							drawY,
							w * SQUARE_SIZE + 1,
							h * SQUARE_SIZE + 1,
							1,0, c.r, c.g, c.b, c.a);
						// Landing pos
						r.drawTexture(drawX,
									  y * SQUARE_SIZE + quickPlacePos.y * SQUARE_SIZE, w * SQUARE_SIZE+1, SQUARE_SIZE,
							          1,0, c.r, c.g, c.b, 125);					
					}
				}
			}

		}
		TETRONIMO getUpcomingTetronimo(int i)
		{
			return upcomingTetronimos[(currentTetronimoIndex + i) % 3];
		}
		void drawUpcomingTetronimo(Core::RendererAdapter& r, unsigned int i, int posX, int posY, float scale, float rot)
		{
			TETRONIMO t = upcomingTetronimos[(currentTetronimoIndex + i) % 3];
			drawGUITetronimo(r, t, posX, posY, scale, rot);
		}
		void drawSavedTetronimo(Core::RendererAdapter& r, int posX, int posY, float scale, float rot)
		{
			if (savedTetronimo != 0)
				drawGUITetronimo(r, savedTetronimo, posX, posY, scale, rot);
		}
		void drawGUITetronimo(Core::RendererAdapter& r, TETRONIMO t, int posX, int posY, float scale, float rot)
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
					{
						//r.drawRectangle(px, py, sSize, sSize, 0.0, c.r, c.g, c.b, c.a);
					}
					else
					{
						r.drawTexture(px, py, scale, rot, c.r, c.g, c.b, 255);

						// Check neighbors
						auto get = [&](int nx, int ny)
						{
							if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4)
								return 0;
							return tetronimos[TETRONIMO_INDEX(t, 1, nx, ny)];
						};

						float outline = 2.0f;

						// Top
						if (get(x, y - 1) == 0)
							r.drawRectangle(px - outline, py - outline, sSize + outline * 2, outline, 0.0f, 255, 255, 255, 255);

						// Bottom
						if (get(x, y + 1) == 0)
							r.drawRectangle(px - outline, py + sSize, sSize + outline * 2, outline, 0.0f, 255, 255, 255, 255);

						// Left
						if (get(x - 1, y) == 0)
							r.drawRectangle(px - outline, py, outline, sSize, 0.0f, 255, 255, 255, 255);

						// Right
						if (get(x + 1, y) == 0)
							r.drawRectangle(px + sSize, py, outline, sSize, 0.0f, 255, 255, 255, 255);
					
					}
				}
			}
		}

		void drawScore(Core::RendererAdapter& r, int x, int y)
		{
			r.drawText(std::to_string(score).c_str(), x, y, 64, 255, 255, 255, 255);
		}
		void drawTrail(Core::RendererAdapter& r)
		{
			Color c = trailColor;

			// Find start and end of the tetronimo
			minPos = { 4,4 };
			maxPos = { -1,-1 };

			calculateTetronimoMinMax(minPos, maxPos, trailTetronimo, trailRot);

			minPos.x += trailStart.x;
			minPos.y += trailStart.y;
			maxPos.x += trailStart.x;
			maxPos.y += trailStart.y;

			r.drawRectangle(
				minPos.x * SQUARE_SIZE,
				minPos.y * SQUARE_SIZE,
				(maxPos.x - minPos.x + 1) * SQUARE_SIZE,
				(trailEndY - minPos.y + 2) * SQUARE_SIZE, 0.0f, c.r, c.g, c.b, c.a);
		}

		void drawGridOutline(Core::RendererAdapter& r)
		{
			int outlineWidth = 2;

			int gridWidthPixels = GRID_WIDTH * SQUARE_SIZE;
			int gridHeightPixels = GRID_HEIGHT * SQUARE_SIZE;

			int x = grid.pos.x * SQUARE_SIZE;
			int y = grid.pos.y * SQUARE_SIZE;

			// Top
			Rectangle top = {
				(float)(x - outlineWidth),
				(float)(y - outlineWidth),
				(float)(gridWidthPixels + outlineWidth * 2),
				(float)outlineWidth
			};

			// Bottom
			Rectangle bottom = {
				(float)(x - outlineWidth),
				(float)(y + gridHeightPixels),
				(float)(gridWidthPixels + outlineWidth * 2),
				(float)outlineWidth
			};

			// Left
			Rectangle left = {
				(float)(x - outlineWidth),
				(float)(y),
				(float)outlineWidth,
				(float)(gridHeightPixels)
			};

			// Right
			Rectangle right = {
				(float)(x + gridWidthPixels),
				(float)(y),
				(float)outlineWidth,
				(float)(gridHeightPixels)
			};

			DrawRectangleRec(top, WHITE);
			DrawRectangleRec(bottom, WHITE);
			DrawRectangleRec(left, WHITE);
			DrawRectangleRec(right, WHITE);
		}

		//

		void calculateTetronimoMinMax(Vector2& min, Vector2& max, TETRONIMO t, int rot)
		{
			// TODO : Cache this for every tetronimo, every rotation - only needs to be done once and then can be saved
			min = { 4,4 };
			max = { -1,-1 };

			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					int currentSquare = tetronimos[TETRONIMO_INDEX(t, rot, x, y)]; // TODO Cache this somewhere
					if (currentSquare != 0)
					{
						if (x < min.x) min.x = x;
						if (y < min.y) min.y = y;
						if (x > max.x) max.x = x;
						if (y > max.y) max.y = y;
					}
				}
			}
		}

		Vector2 calculateTetronimoCentre(Vector2 min, Vector2 max)
		{
			return { float(min.x + max.x + 1) / 2.0f, float(min.y + max.y + 1) / 2.0f };
		}



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
			PlaySound(Core::Application::Get().GetAssetManager().getSound("Place"));
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
			currentDepth = 2;
			currentTetronimoIndex = ((currentTetronimoIndex + 1) % 3);				   //   increment index position for the next tetronimo
			currentTetronimo = upcomingTetronimos[currentTetronimoIndex]; //				set the next tetronimo as current
			upcomingTetronimos[currentTetronimoIndex] = TETRONIMO(rand() % (7) + 1); //		get new random tetronimo
			quickPlacePos = getLandingPosition();

			if (checkCollision(currentPos))
			{
				PlaySound(Core::Application::Get().GetAssetManager().getSound("Fail"));
				gameOver = true;
			}
			
		}

		void initNextTetronimo(TETRONIMO t)
		{
			currentPos = { 3, 0 };
			currentRotation = 0;
			currentDepth = (rand() % 64 + 2) / 2;
			currentDepth = 2;
			currentTetronimoIndex = ((currentTetronimoIndex + 1) % 3);				   //   increment index position for the next tetronimo
			currentTetronimo = t; //				set the next tetronimo as current
			upcomingTetronimos[currentTetronimoIndex] = TETRONIMO(rand() % (7) + 1); //		get new random tetronimo
			quickPlacePos = getLandingPosition();

			if (checkCollision(currentPos))
			{
				PlaySound(Core::Application::Get().GetAssetManager().getSound("Fail"));
				gameOver = true;
			}
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

			// Find location of full lines
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
					PlaySound(Core::Application::Get().GetAssetManager().getSound("LineComplete"));
					for (int x = 0; x < GRID_WIDTH; x++)
					{
						Vector2 _pos = Vector2{ (float)(x + grid.pos.x + 0.5f) * SQUARE_SIZE, float(y + 1 - 0.5f) * SQUARE_SIZE };

						// Line of particles, the same colour as the background, last until the grid is moved down
						Core::Particle pEmptyGrid;
						pEmptyGrid.pos = _pos;
						pEmptyGrid.sizeStart = Vector2{ SQUARE_SIZE, SQUARE_SIZE };
						pEmptyGrid.sizeEnd = Vector2{ SQUARE_SIZE, SQUARE_SIZE };
						pEmptyGrid.colorStart = colors[0];
						pEmptyGrid.colorEnd = colors[0];
						pEmptyGrid.lifetime = 0.5f / 2; // TODO Add constants to magic numbers
						pEmptyGrid.rotationStart = 0.f;
						pEmptyGrid.rotationEnd = 0.f;
						particleSystem.AddParticle(pEmptyGrid);

						// Line of white particles, fading out
						Core::Particle pFade;
						pFade.pos = _pos;
						pFade.sizeStart = Vector2{ SQUARE_SIZE-1, SQUARE_SIZE-1 };
						pFade.sizeEnd = Vector2{ SQUARE_SIZE-1, SQUARE_SIZE-1};
						pFade.colorStart = Color{255, 255,255, 255};
						pFade.colorEnd = Color{255, 255, 255, 0};
						pFade.lifetime = 1.0f / 2;
						pFade.rotationStart = 0.f;
						pFade.rotationEnd = 0.f;
						particleSystem.AddParticle(pFade);

						// Line of rotating particles, created left to right with alarm
						Core::Particle p;
						p.pos = _pos;
						p.velocity = Vector2{ 0, -32 };
						p.sizeStart = Vector2{ SQUARE_SIZE, SQUARE_SIZE };
						p.sizeEnd = Vector2{ 0.1, 0.1};
						p.colorStart = WHITE;
						p.colorEnd = WHITE;
						p.age = 0.0f;
						p.lifetime = 1.0f / 2;
						p.rotationStart = 0.f;
						p.rotationEnd = 1.57 * 40;
						
						Core::Application::Get().PushAlarm(Core::Alarm([=]() 
						{
							particleSystem.AddParticle(p);
						}, float(x) / GRID_WIDTH / 4));


					}

				}
				
			}

			
				

			score += combo * 4;

			int write_y = GRID_HEIGHT - 1;
			
			// In order to prevent any movement while we wait for the grid to be shifted down
			alarmOngoing = true;
			Core::Application::Get().PushAlarm(Core::Alarm([=]() {alarmOngoing = false; }, 0.5f / 2));

			// Shift down grid
			for (int y = GRID_HEIGHT-1; y >= 0; y--)
			{
				if (!linesFull[y]) {
					for (int x = 0; x < GRID_WIDTH; x++)
					{
						Core::Application::Get().PushAlarm(Core::Alarm([=]()
						{
							grid.getSquare(x, write_y) = grid.getSquare(x, y); // i dont think this needs to be 2 for loops
							grid.getDepth(x, write_y) = grid.getDepth(x, y);
						}, 0.5f / 2 ));




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