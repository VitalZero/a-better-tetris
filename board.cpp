#include "board.h"
#include <cassert>
#include "assetmanager.h"

Board::Board(const Location& loc, int size)
	:
	loc({loc.x + 1, loc.y}), tileSize(size) // increase x and y so the border is not drawn outside
{
	//texture = AssetManager::LoadSprite("resources/blocks.png");
	//

	for(int y = 0; y < tileHeight; ++y)
	{
		for(int x = 0; x < tileWidth; ++x)
		{
			grid[y * tileWidth + x] = (int)BlockType::Empty;
		}
	}
}

void Board::Draw()
{	
	for(int y = 0; y < tileHeight; ++y)
	{
		for(int x = 0; x < tileWidth; ++x)
		{
			int x1 = (x * tileSize) + 1 + (loc.x * tileSize);
			int y1 = (y * tileSize) + 1 + (loc.y * tileSize);

			int size = tileSize - 1;

			int tileValue = TileAt(x, y);
			assert(tileValue < 7);

			// if(tileValue == (int)BlockType::Empty)
			// {
			// 	DrawRectangle(x1, y1, size, size, {30, 30, 30, 255});
			// }
			// else if(tileValue == (int)BlockType::ToDelete)
			// {
			// 	DrawRectangle(x1, y1, size, size, DARKBROWN);
			// }
			//else
			if(tileValue > (int)BlockType::Empty)
			{
				//DrawRectangle(x1, y1, size, size, TetrominoColors[tileValue]);
				int spriteX = tileValue * tileSize;
				DrawTextureRec(*texture, {(float)spriteX, 0, (float)tileSize, (float)tileSize}, {(float)x1-1, (float)y1-1}, WHITE);
			}
		}
	}
}

int Board::TileAt(int x, int y) const
{
	assert(x >= 0);
	assert(x < tileWidth);
	assert(y >= 0);
	assert(y < tileHeight);

	return grid[y * tileWidth + x];
}

void Board::SetTile(int x, int y, int value)
{
	assert(x >= 0);
	assert(x < tileWidth);
	assert(y >= 0);
	assert(y < tileHeight);

	grid[y * tileWidth + x] = value;
}

Location Board::GetLocation() const
{
	return loc;
}

void Board::CheckAndDeleteLines()
{
	int y1 = tileHeight - 1;

	for(int y = y1; y > 0; --y)
	{
		int xCount = 0;

		for(int x = 0; x < tileWidth; ++x)
		{
			if(TileAt(x, y) >= 0)
				++xCount;
			
			SetTile(x, y1, TileAt(x, y));
		}

		if(xCount < tileWidth)
			--y1;
	}
}

void Board::Init()
{
	texture = AssetManager::LoadSprite("resources/blocks.png");

	bg = LoadRenderTexture(tileWidth * tileSize, tileHeight * tileSize);

	BeginTextureMode(bg);
	ClearBackground(GRAY);
	
	for(int x = 0; x < tileWidth; ++x)
	{
		DrawLine(x * tileSize, 0, x * tileSize, tileHeight * tileSize - 1, BLACK);
	}

	for(int y = 0; y < tileHeight; ++y)
	{
		DrawLine(0, y * tileSize, tileWidth * tileSize - 1, y * tileSize, BLACK);
	}

	EndTextureMode();
}

void Board::CleanUp()
{
	UnloadRenderTexture(bg);
	UnloadTexture(*texture);
}

void Board::DrawBorders()
{
	DrawTexture(bg.texture, loc.x * tileSize, loc.y * tileSize, WHITE);
}