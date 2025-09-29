#pragma once
#include <array>
#include <Tetronimos.h>
#include <raylib.h>



namespace Tetris
{
	constexpr int SQUARE_SIZE = 32;
	constexpr int GRID_WIDTH = 10;
	constexpr int GRID_HEIGHT = 20;


	constexpr enum TETRONIMO
	{
		IBlock = 0,
		JBlock,
		LBlock,
		OBlock,
		SBlock,
		TBlock,
		ZBlock

	};

	struct Tetris
	{
		std::array<int, GRID_WIDTH* GRID_HEIGHT> grid = {0};
		int score = 0;

		TETRONIMO currentTetronimo = IBlock;
		int currentRotation = 0;
		Vector2 currentPos = {3, 0};
		
	};

}