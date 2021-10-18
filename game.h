#pragma once
#include <string>
#include "board.h"
#include "tetromino.h"
#include "location.h"
#include <random>
#include "gamedata.h"

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
	GameDataRef data = std::make_shared<GameData>();
};