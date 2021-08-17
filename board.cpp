#include "board.h"
#include <cassert>

Board::Board(const Location& loc, int size)
	:
	loc({loc.x + 1, loc.y}), tileSize(size) // increase x and y so the border is not drawn outside
{
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
	//DrawBorders();
	
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
				DrawRectangle(x1, y1, size, size, TetrominoColors[tileValue]);
				//DrawRectangleLinesEx({(float)x1, (float)y1, (float)size, (float)size}, 1, DARKBLUE);
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

void Board::DrawBorders()
{
	int x1 = (loc.x - 1) * tileSize;
	int y1 = loc.y * tileSize;
	DrawRectangleLines(x1, y1, tileSize, tileHeight * tileSize, BLUE);//{250, 252, 251, 255}); // left border
	DrawRectangleLines(x1 + tileSize + (tileWidth * tileSize) + 1, y1, tileSize + 1, tileHeight * tileSize, BLUE);//{250, 252, 251, 255}); // right border
	DrawRectangleLines(x1, y1 + tileHeight * tileSize, (tileWidth * tileSize) + (tileSize * 2) + 2, tileSize, BLUE);//{250, 252, 251, 255}); // bottom border
}