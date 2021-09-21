#pragma once
#include <vector>
#include <raylib.h>
#include "location.h"
#include "board.h"
#include <random>
#include <memory>
#include "assetmanager.h"

using Figure = std::vector<Vector2>;

class Tetromino
{
public:
	enum class MinoType { None = -1, S, T, O, L, J, Z, I };

public:
	Tetromino(const Location& loc, int size, Board& brd);
	~Tetromino();
	Tetromino(const Tetromino&) = delete;
	Tetromino(const Tetromino&&) = delete;
	void Draw();
	//void DrawG();
	void Init(MinoType in_next, MinoType incurrent = MinoType::None);
	bool Rotate();
	void MoveBy(const Location& in_loc);
	Location GetLocation() const { return loc; }
	//bool HasLanded() const { return landed; }
	void DrawNextTetromino(int x, int y, int size);
	int PutPieceOnBoard();
	bool CheckCollision();
	bool CanMoveX(int dx) const;
	bool CanMoveY(int dy) const;

private:
	void RotateRight();
	void RotateLeft();
	//int DrawGhost();

private:
	Location loc;
	const Location initialLoc;
	int size;
	Color color;
	Figure figure;
	Board& board;
	MinoType currentType = MinoType::None;
	MinoType nextType = MinoType::None;
	bool landed = false;
	static constexpr Vector2 figuresList[7][4]= 
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