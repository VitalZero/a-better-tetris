#include "tetromino.h"
#include <cassert>
#include <cmath>
#include <algorithm>

Tetromino::Tetromino(const Location& loc, int size, Board& board)
	:
	figure(4), loc(loc), initialLoc(loc), size(size), board(board)
{
	Reset();
}

Tetromino::Tetromino(int x, int y, int size, Board& board)
	:
	loc({x, y}), initialLoc({x, y}), size(size), board(board)
{
	Reset();
}

void Tetromino::Draw()
{
	Location brdLoc = board.GetLocation();

	for(const auto& f : figure)
	{
		int x1 = f.x + loc.x + brdLoc.x;
		int y1 = f.y + loc.y + brdLoc.y;

		//DrawRectangleLines(x1 * size + 1, (yOffset + y1) * size + 1, size - 1, size - 1, RED);
		DrawRectangle(x1 * size + 1, y1 * size + 1, size - 1, size - 1, color);
	}

}

void Tetromino::DrawG()
{
	Location brdLoc = board.GetLocation();

	int yOffset = DrawGhost();

	for(const auto& f : figure)
	{
		int x1 = f.x + loc.x + brdLoc.x;
		int y1 = f.y + loc.y + brdLoc.y;

		DrawRectangleLinesEx({(float)x1 * size + 1, (float)(yOffset + y1) * size + 1, (float)size - 1, (float)size - 1}, 2, SKYBLUE);
	}

}

void Tetromino::Reset()
{
	figure.clear();

	loc = initialLoc;

	std::uniform_int_distribution<int> colorDst(0, 4);
	std::uniform_int_distribution<int> figureDst(0, 6);
	
	colorIndex = colorDst(rng);

	color = Board::TetrominoColors[colorIndex];

	int figureIndex = figureDst(rng);

	minoType = (MinoType)figureIndex;

	for(int i = 0; i < 4; ++i)
	{
		figure.emplace_back(figuresList[figureIndex][i]);
	}
}

void Tetromino::Rotate()
{
	if(minoType != MinoType::O)
	{
		RotateRight();

		if(!CanMove())
			RotateLeft();
	}
}

void Tetromino::MoveBy(const Location& offset_loc)
{
	assert(offset_loc.x >= -1 && offset_loc.x <= 1);
	assert(offset_loc.y >= -1 && offset_loc.y <= 1);

	Location tmp = loc;

	loc.Add(offset_loc);

	if(!CanMove())
	{
		if(offset_loc.y > 0)
		{
			loc = tmp;
			PutPieceOnBoard();
			Reset();
		}
		else
		{
			loc = tmp;
		}
	}
}

void Tetromino::RotateLeft()
{
	for(auto& f : figure)
	{
		int tmpX = f.x;
		f.x = f.y;
		f.y = -tmpX;
	}
}

void Tetromino::RotateRight()
{
	for(auto& f : figure)
	{
		int tmpX = f.x;
		f.x = -f.y;
		f.y = tmpX;
	}
}

bool Tetromino::CanMove()
{
	for(const auto& f : figure)
	{
		if((f.x + loc.x) >= board.tileWidth ||
			(f.y + loc.y) >= board.tileHeight)
			return false;
		else if((f.x + loc.x) < 0 || (f.y + loc.y) < 0)
			return false;
		if(board.TileAt(f.x + loc.x, f.y + loc.y) >= 0)
			return false;
	}

	return true;
}

void Tetromino::PutPieceOnBoard()
{
	for(const auto& f : figure)
	{
		board.SetTile(f.x + loc.x, f.y + loc.y, colorIndex);
	}

	board.CheckAndDeleteLines();
}

int Tetromino::DrawGhost()
{
	int yOffset = board.tileHeight - 1;

	for(int yStart = loc.y; yStart < board.tileHeight; ++yStart)
	{
		for(const auto& f : figure)
		{

			if((f.y + yStart) >= board.tileHeight)
			{
				return yStart - loc.y - 1;
			}
			else if(board.TileAt(f.x + loc.x, f.y + yStart) >= 0)
			{
				return yStart - loc.y - 1;
			}
		}
	}

	return board.tileHeight - 1 - loc.y;
}