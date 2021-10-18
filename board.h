#pragma once

#include <raylib.h>
#include "location.h"
#include <memory>
#include "gamedata.h"
#include <vector>

class Board
{
public:
	Board(const Location& loc, int size, GameDataRef data);
	~Board();
	Board(const Board&) = delete;
	Board(const Board&&) = delete;
	void Init();
	void Update(float dt);
	void Draw();
	int TileAt(int x, int y) const;
	void SetTile(int x, int y, int value);
	Location GetLocation() const { return loc; }
	int CheckAndMarkLines();
	void DeleteLines();
	bool IsDeleting() const { return deleting; }
	
	
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
	std::vector<int> grid;
	std::vector<int> linesToDelete = {};
	Texture2D* texture;
	RenderTexture2D bg;
	int drawTimer = 0;
	float frameAccumulator = 0.0f;
	bool deleting = false;
};