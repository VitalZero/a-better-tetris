#pragma once
#include <vector>
#include <raylib.h>
#include "location.h"
#include "board.h"
#include <random>
#include <memory>
#include "assetmanager.h"

struct Block
{
	int x;
	int y;
};

struct CollisionType
{
	int left = 0;
	int right = 0;
	int bottom = 0;
};

using Figure = std::vector<Block>;

class Tetromino
{
public:
	enum class MinoType { None = -1, S, T, O, L, J, Z, I };

public:
	Tetromino(const Location& loc, int size, Board& brd);
	void Draw();
	void DrawG();
	void Init(MinoType in_type);
	void SetNext(MinoType in_type) { nextType = in_type; }
	MinoType GetNext() const { return nextType; }
	bool Rotate();
	bool MoveBy(const Location& in_loc);
	Location GetLocation() const { return loc; }
	bool IsLanded() const { return landed; }
	void DrawNextTetromino(int x, int y, int size);
	void PutPieceOnBoard();
	void CleanUp();

private:
	void RotateRight();
	void RotateLeft();
	bool CheckCollision();
	int DrawGhost();

private:
	Location loc;
	const Location initialLoc;
	int size;
	Color color;
	int colorIndex;
	Figure figure;
	Board& board;
	MinoType currentType = MinoType::None;
	MinoType nextType = MinoType::None;
	bool landed = false;
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

	std::shared_ptr<Texture2D> texture;
};