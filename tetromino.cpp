#include "tetromino.h"
#include <cassert>
#include <cmath>
#include <algorithm>

Tetromino::Tetromino(const Location& loc, int size, Board& board)
	:
	figure(4), loc(loc), initialLoc(loc), size(size), board(board)
{
	Init((MinoType)1);
}

void Tetromino::Draw()
{
	Location brdLoc = board.GetLocation();

	for(const auto& f : figure)
	{
		int x1 = f.x + loc.x + brdLoc.x;
		int y1 = f.y + loc.y + brdLoc.y;

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

		DrawRectangleLinesEx({(float)x1 * size + 1, (float)(yOffset + y1) * size + 1, (float)size - 1, (float)size - 1}, 1, Fade(MAROON, 0.5f));
	}

}

void Tetromino::Init(MinoType in_type)
{
	landed = false;

	figure.clear();

	loc = initialLoc;

	color = Board::TetrominoColors[(int)in_type];
	colorIndex = (int)in_type;

	for(int i = 0; i < 4; ++i)
	{
		figure.emplace_back(figuresList[(int)in_type][i]);
	}
}

bool Tetromino::Rotate()
{
	if(currentType != MinoType::O)
	{
		RotateRight();

		if(!CanMove())
		{
			RotateLeft();
			return false;
		}

		return true;
	}

	return false;
}

bool Tetromino::MoveBy(const Location& offset_loc)
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
			//PutPieceOnBoard();
			//Init(nextType);
			landed = true;
			return true;
		}
		else
		{
			loc = tmp;
		}
	}

	return false;
}

void Tetromino::DrawNextTetromino(int x, int y, int size)
{
	for(int i = 0; i < 4; ++i)
	{
		int x1 = (figuresList[(int)nextType][i].x * size) + x;
		int y1 = (figuresList[(int)nextType][i].y * size) + y;

		DrawRectangle(x1 + 1, y1 + 1, size - 1, size - 1, Board::TetrominoColors[(int)nextType]);
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