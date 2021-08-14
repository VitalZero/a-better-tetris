#pragma once
#include <string>
#include "board.h"
#include "tetromino.h"
#include "location.h"
#include <raylib.h>
#include "mino.h"

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
	Mino nextPiece;
	static constexpr int movePeriod = 50;
	static constexpr int cellSize = 30;
	int moveCounter = 0;
	Shader shader;
	RenderTexture2D target;
	Music bgm;
	Sound moveSound;
	Sound rotateSound;
	Sound lockSound;
};