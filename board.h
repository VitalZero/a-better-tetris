#pragma once

#include <raylib.h>
#include "location.h"

class Board
{
public:
	Board(const Location& loc, int size);
	void Draw();
	int TileAt(int x, int y) const;
	void SetTile(int x, int y, int value);
	Location GetLocation() const;
	void CheckAndDeleteLines();
	
public:
	static constexpr int tileWidth = 12;
	static constexpr int tileHeight = 20;
	const int tileSize;
	static constexpr Color TetrominoColors[7] = 
	{ BLUE, GREEN, RED, YELLOW, ORANGE, GRAY, PURPLE };
	enum class BlockType { ToDelete = -2, Empty = -1 };

public:
	void DrawBorders();

private:
	const Location loc;
	int grid[tileWidth * tileHeight] = {};
};