#pragma once
#include <vector>
#include <raylib.h>
#include "location.h"
#include "board.h"
#include <random>

class Tetromino
{
private:
	struct Block
	{
		int x;
		int y;
	};

public:
	Tetromino(const Location& loc, int size, Board& brd);
	Tetromino(int x, int y, int size, Board& board);
	void Draw();
	void Reset();
	void Rotate();
	void MoveBy(const Location& in_loc);

private:
	void RotateRight();
	void RotateLeft();
	bool CanMove();
	void PutPieceOnBoard();
	int DrawGhost();

private:
	Location loc;
	const Location initialLoc;
	int size;
	Color color;
	int colorIndex;
	std::vector<Block> figure;
	Board& board;
	std::mt19937 rng{std::random_device()()};

	static constexpr Block figuresList[7][4]= 
	{
		{ {0, 0}, {1, 0},  {-1, 1},  {0, 1} }, // S
		{ {0, 0}, {-1, 0},  {1, 0}, {0, 1} }, // T
		{ {0, 0},  {1, 0},  {0, 1},  {1, 1} }, // O
		{ {0, 0}, {-1, 0},  {1, 0},  {-1, 1} }, // L
		{ {0, 0}, {-1, 0},  {1, 0},  {1, 1} }, // J
		{ {0, 0}, {-1, 0}, {0, 1},  {1, 1} },// Z
		{ {0, 0}, {-1, 0},  {1, 0},  {2, 0} }  // I
	};
};