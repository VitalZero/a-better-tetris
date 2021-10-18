#include "board.h"
#include <cassert>
#include "assetmanager.h"
#include <algorithm>

Board::Board(const Location& loc, int size, GameDataRef data)
	:
	loc({loc.x, loc.y}), tileSize(size), grid(tileWidth * tileHeight) // increase x and y so the border is not drawn outside
{
	texture = data->assets.LoadAsset<Texture2D>("resources/blocks32x32.png");

	bg = LoadRenderTexture(tileWidth * tileSize, tileHeight * tileSize);

	BeginTextureMode(bg);
	ClearBackground(Fade(LIGHTGRAY, 0.0f));

	for(int y = 0; y < tileHeight - 1; ++y)
	{
		for(int x = 1; x < tileWidth - 1; ++	x)
		{
			DrawTextureRec(*texture, {(float)tileSize * 7, 0, (float)tileSize, (float)tileSize}, {(float)x * tileSize, (float)y * tileSize}, Fade(WHITE, 1.0f));
		}
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

void Board::Update(float dt)
{
	frameAccumulator += dt;

	if(frameAccumulator >= 1.0f / 60.0f)
	{
		if(deleting)
		{
			++drawTimer;

			if(drawTimer >= 30)
			{
				deleting = false;
				DeleteLines();
				drawTimer = 0.0f;
			}
		}

		frameAccumulator = 0.0f;
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
			int spriteX = (tileValue) * tileSize;

			if(tileValue > (int)BlockType::Empty && tileValue != (int)BlockType::Wall)
			{
				DrawTextureRec(*texture, {(float)spriteX, 0, (float)tileSize, (float)tileSize}, {(float)x1, (float)y1}, WHITE);
			}
			else if(tileValue == (int)BlockType::ToDelete)
			{
				Color c;
				if(drawTimer % 12 < 6)
					c = RAYWHITE;
				else
					c = MAROON;

				DrawRectangle(x1, y1, tileSize, tileSize, c);
			}
			// else if(tileValue == (int)BlockType::Wall)	// dont draw the wall at the moment
			// {
			// 	DrawRectangle(x1, y1, tileSize, tileSize, DARKGRAY);
			// }
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

int Board::CheckAndMarkLines()
{
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
			linesToDelete.push_back(y);

			// for(int x = 1; x < tileWidth - 1; ++x)
			// {
			// 	SetTile(x, y, (int)BlockType::ToDelete);
			// }

			++deletedLines;
		}
	}

	if(deletedLines > 0)	
		deleting = true;

	if(!linesToDelete.empty())
	{
		std::sort(linesToDelete.begin(), linesToDelete.end(), std::greater<int>{});
	}

	return deletedLines;
}

void Board::DeleteLines()
{
	// int y1 = tileHeight - 2;
	// for(int y = 0; y < tileHeight - 1; ++y)
	// {
	// 	if(TileAt(1, y) == (int)BlockType::ToDelete)
	// 	{
	// 		for(int upY = y; upY >= 0; --upY)
	// 		{
	// 			for(int x = 1; x < tileWidth - 1; ++x)
	// 			{
	// 				if(upY == 0)
	// 				{
	// 					SetTile(x, upY, (int)BlockType::Empty);
	// 				}
	// 				else if(upY > 0)
	// 				{
	// 					SetTile(x, upY, TileAt(x, upY - 1));
	// 				}
	// 			}
	// 		}
	// 	}
	// }

	while(!linesToDelete.empty())
	{
		int y = linesToDelete.back();

		// go up and copy 1 cell down
		for(int yUp = y; yUp >= 0; --yUp)
		{
			for(int x = 1; x < tileWidth - 1; ++x)
			{
				if(yUp == 0)
				{
					SetTile(x, yUp, (int)BlockType::Empty);
				}
				else if(yUp > 0)
				{
					SetTile(x, yUp, TileAt(x, yUp - 1));
				}
			}
		}

		linesToDelete.pop_back();
	}

}

void Board::DrawBorders()
{
	DrawTextureRec(bg.texture, { 0, 0, (float)bg.texture.width, (float)-bg.texture.height},
		{ (float)loc.x * tileSize, (float)loc.y * tileSize }, WHITE);
}