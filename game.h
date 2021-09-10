#pragma once
#include <string>
#include "board.h"
#include "tetromino.h"
#include "location.h"
#include <random>
#include "assetmanager.h"

class Game
{
public:
	Game();
	Game(const Game&) = delete;
	Game(const Game&&) = delete;
	~Game();
	void Run();

private:
	void Input();
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
	Location offset = {};
	bool pause = false;
};