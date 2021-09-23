#include "board.h"
#include <cassert>
#include "assetmanager.h"

Board::Board(const Location& loc, int size)
	:
	loc({loc.x, loc.y}), tileSize(size) // increase x and y so the border is not drawn outside
{
	texture = AssetManager::LoadSprite("resources/blocks.png");

	bg = LoadRenderTexture(tileWidth * tileSize, tileHeight * tileSize);

	BeginTextureMode(bg);
	ClearBackground(LIGHTGRAY);

	for(int x = 0; x < tileWidth; ++x)
	{
		DrawLine(x * tileSize , 0, x * tileSize, tileHeight * tileSize, GRAY);
	}

	for(int y = 0; y < tileHeight; ++y)
	{
		DrawLine(0, y * tileSize, tileWidth * tileSize, y * tileSize, GRAY);
	}

	EndTextureMode();

	Init();
}

Board::~Board()
{
	UnloadRenderTexture(bg);
}

void Board::Init()
{
	for(int y = 0; y < tileHeight; ++y)
	{
		for(int x = 0; x < tileWidth; ++x)
		{
			if(x == 0 || x == tileWidth - 1 || y == tileHeight - 1)
			{
				grid[y * tileWidth + x] = (int)BlockType::Wall;
			}
			else
			{
				grid[y * tileWidth + x] = (int)BlockType::Empty;
			}
		}
	}
}

void Board::Update()
{
	if(deleting)
	{
		++drawTimer;

		if(drawTimer >= 30)
		{
			deleting = false;
			DeleteLines();
			drawTimer = 0;
		}
	}
}

void Board::Draw()
{
	for(int y = 0; y < tileHeight; ++y)
	{
		for(int x = 0; x < tileWidth; ++x)
		{
			int x1 = (x * tileSize) + (loc.x * tileSize);
			int y1 = (y * tileSize) + (loc.y * tileSize);

			int size = tileSize;

			int tileValue = TileAt(x, y);
			assert(tileValue < 7 || tileValue == (int)BlockType::Wall);

			if(tileValue > (int)BlockType::Empty && tileValue != (int)BlockType::Wall)
			{
				int spriteX = tileValue * tileSize;
				DrawTextureRec(*texture, {(float)spriteX + 30, 0, (float)tileSize, (float)tileSize}, {(float)x1, (float)y1}, WHITE);
			}
			else if(tileValue == (int)BlockType::ToDelete)
			{
				Color c;
				if(drawTimer % 6 < 3)
					c = RAYWHITE;
				else
					c = MAROON;

				DrawRectangle(x1, y1, tileSize, tileSize, c);
			}
			else if(tileValue == (int)BlockType::Wall)
			{
				DrawRectangle(x1, y1, tileSize, tileSize, GRAY);
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

int Board::CheckAndMarkLines()
{
	// int y1 = tileHeight - 2;

	// for(int y = y1; y1 >= 0; --y)
	// {
	// 	int xCount = 0;

	// 	for(int x = 1; x < tileWidth - 1; ++x)
	// 	{
	// 		if(y >= 0)
	// 		{
	// 			if(TileAt(x, y) >= 0)
	// 				++xCount;

	// 			SetTile(x, y1, TileAt(x, y));
	// 		}
	// 		else
	// 		{
	// 			SetTile(x, y1, (int)BlockType::Empty);
	// 		}
	// 	}

	// 	if(xCount < tileWidth - 2)
	// 		--y1;
	// }

	int deletedLines = 0;

	for(int y = 0; y < tileHeight - 1; ++y)
	{
		int xCounter = 0;

		for(int x = 1; x < tileWidth - 1; ++x)
		{
			if(TileAt(x, y) == (int)BlockType::Empty)
			{
				break;
			}
			else
			{
				++xCounter;
			}
		}

		if(xCounter >= 10)
		{
			// for(int upY = y; upY >= 0; --upY)
			// {
			// 	for(int x = 1; x < tileWidth - 1; ++x)
			// 	{
			// 		if(upY == 0)
			// 		{
			// 			SetTile(x, upY, (int)BlockType::Empty);
			// 		}
			// 		else if(upY > 0)
			// 		{
			// 			SetTile(x, upY, TileAt(x, upY - 1));
			// 		}
			// 	}
			// }

			for(int x = 1; x < tileWidth - 1; ++x)
			{
				SetTile(x, y, (int)BlockType::ToDelete);
			}

			++deletedLines;
		}
	}

	numFullLines = deletedLines;

	if(deletedLines > 0)	
		deleting = true;

	return deletedLines;
}

void Board::DeleteLines()
{
	int y1 = tileHeight - 2;
	for(int y = 0; y < tileHeight - 1; ++y)
	{
		if(TileAt(1, y) == (int)BlockType::ToDelete)
		{
			for(int upY = y; upY >= 0; --upY)
			{
				for(int x = 1; x < tileWidth - 1; ++x)
				{
					if(upY == 0)
					{
						SetTile(x, upY, (int)BlockType::Empty);
					}
					else if(upY > 0)
					{
						SetTile(x, upY, TileAt(x, upY - 1));
					}
				}
			}
		}
	}

	numFullLines = 0;
}

void Board::DrawBorders()
{
	DrawTextureRec(bg.texture, { 0, 0, (float)bg.texture.width, (float)-bg.texture.height},
		{ (float)loc.x * tileSize, (float)loc.y * tileSize }, WHITE);
}