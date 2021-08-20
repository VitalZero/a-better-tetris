#pragma once
#include <string>
#include "board.h"
#include "tetromino.h"
#include "location.h"
#include <random>

class Game
{
public:
	Game(int x, int y, const std::string& title);
	void Run();

private:
	void Update();
	void Draw();

private:
	Board board;
	Tetromino mainPiece;
	static constexpr int movePeriod = 50;
	static constexpr int cellSize = 30;
	int moveCounter = 0;
	int lateralCounter = 7;
	std::mt19937 rng{std::random_device()()};
	std::uniform_int_distribution<int> minoDst;
	Texture2D tetrominoTexture;
	Texture2D bg;
};