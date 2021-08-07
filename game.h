#pragma once
#include <string>
#include "board.h"
#include "tetromino.h"
#include "location.h"

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
	Tetromino nextPiece;
	static constexpr int movePeriod = 50;
	static constexpr int cellSize = 30;
	int moveCounter = 0;
};