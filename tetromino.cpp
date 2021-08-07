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

	int yOffset = DrawGhost();

	for(const auto& f : figure)
	{
		int x1 = f.x + loc.x + brdLoc.x;
		int y1 = f.y + loc.y + brdLoc.y;

		DrawRectangle(x1 * size + 1, y1 * size + 1, size - 1, size - 1, color);
		DrawRectangleLines(x1 * size + 1, (yOffset + y1) * size + 1, size - 1, size - 1, RED);
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

	for(int i = 0; i < 4; ++i)
	{
		figure.emplace_back(figuresList[figureIndex][i]);
	}
}

void Tetromino::Rotate()
{
	RotateRight();

	if(!CanMove())
		RotateLeft();
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

	// if(board.CheckFilledLines())
	// {
	// 	board.DeleteMarkedLines();
	// }
}

int Tetromino::DrawGhost()
{
	int yOffset = board.tileHeight - 1;

	auto sizz = figure.size();

	for(const auto& f : figure)
	{
		int yCheck = f.y + this->loc.y;
		int x = f.x + this->loc.x;

		while(yCheck < board.tileHeight)
		{
		 	if(board.TileAt(x, yCheck) >= 0)
		 		break;

			++yCheck;
		}

		yOffset = std::min(yOffset, yCheck);
	}

	return yOffset;
}