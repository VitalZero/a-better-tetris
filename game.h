#pragma once
#include <string>
#include "board.h"
#include "tetromino.h"
#include "location.h"
#include <random>
#include "assetmanager.h"
#include "wrappers.h"

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
	void Update(float dt);
	void Draw();

private:
	Board board;
	Tetromino mainPiece;
	static constexpr int movePeriod = 50;
	static constexpr int cellSize = 30;
	static constexpr int lateralCounterPeriod = 7;
	int secTimer = 0;
	int moveCounter = 0;
	int lateralCounter = 7;
	std::mt19937 rng{std::random_device()()};
	std::uniform_int_distribution<int> minoDst;
	Location offset = {};
	bool pause = false;
	bool deleting = false;
	enum class States { StartScreen, Game, Pause, Deleting, GameOver };
	States currentState;
	float frameTime = 0;
	std::shared_ptr<Music> music;
	std::shared_ptr<Sound> moveSound;
	std::shared_ptr<Sound> rotateSound;
	std::shared_ptr<Sound> landSound;
	std::shared_ptr<Sound> lineSound;
	std::shared_ptr<CTexture2D> testTexture;
};