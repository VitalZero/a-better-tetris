#pragma once

#include <raylib.h>
#include "location.h"
#include <memory>

class Board
{
public:
	Board(const Location& loc, int size);
	~Board();
	Board(const Board&) = delete;
	Board(const Board&&) = delete;
	void Draw();
	int TileAt(int x, int y) const;
	void SetTile(int x, int y, int value);
	Location GetLocation() const;
	int CheckAndDeleteLines();
	
public:
	static constexpr int tileWidth = 12;
	static constexpr int tileHeight = 20;
	const int tileSize;
	static constexpr Color TetrominoColors[7] = 
	{ BLUE, GREEN, RED, YELLOW, ORANGE, GRAY, PURPLE };
	enum class BlockType { ToDelete = -2, Empty = -1, Wall = 10 };

public:
	void DrawBorders();

private:
	const Location loc;
	int grid[tileWidth * tileHeight] = {};
	std::shared_ptr<Texture2D> texture;
	RenderTexture2D bg;
};