#pragma once
#include "Istate.h"
#include "gamedata.h"
#include "tetromino.h"
#include "board.h"
#include "raylib.h"

class GameState : public IState
{
public:
    GameState(GameDataRef data);
    ~GameState();
    void Init() override;
    void Input()override;
    void Update(float dt) override;
    void Draw() override;
	void Resume();

private:
    GameDataRef data;
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
	float frameTime = 0;
	std::shared_ptr<Music> music;
	std::shared_ptr<Sound> moveSound;
	std::shared_ptr<Sound> rotateSound;
	std::shared_ptr<Sound> landSound;
	std::shared_ptr<Sound> lineSound;
	std::shared_ptr<Texture2D> testTexture;
};