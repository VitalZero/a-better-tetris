#include "tetromino.h"
#include <cassert>
#include <cmath>
#include <algorithm>

Tetromino::Tetromino(const Location& loc, int size, Board& board, GameDataRef data)
	:
	figure(4), loc(loc), initialLoc(loc), size(size), board(board)
{
	texture = data->assets.LoadAsset<Texture2D>("resources/blocks32x32.png");
}

Tetromino::~Tetromino()
{
}

void Tetromino::Draw()
{
	Location brdLoc = board.GetLocation();

	for(const auto& f : figure)
	{
		float x1 = (f.x + loc.x + brdLoc.x) * size;
		float y1 = (f.y + loc.y + brdLoc.y) * size;

		int spriteX = ((int)currentType) * size;
		DrawTextureRec(*texture, {(float)spriteX, 0, (float)size, (float)size}, {x1, y1}, WHITE);
	}
}

void Tetromino::DrawGuide()
{
	Location brdLoc = board.GetLocation();

	for(const auto& f : figure)
	{

		int x = f.x + loc.x + brdLoc.x;
		int y = brdLoc.y + nearestBottomCollision + f.y;
		int spriteX = (int)currentType * size;
		DrawRectangleLinesEx({(float)x * size, (float)y * size, (float)size, (float)size}, 2, MAROON);
		//DrawTextureRec(*texture, {(float)spriteX, 0, (float)size, (float)size}, {(float)x1 * size, (float)(yOffset + y1) * size}, Fade(WHITE, 0.3f));
	}

}

void Tetromino::Init(MinoType in_next, MinoType in_current)
{
	figure.clear();

	loc = initialLoc;

	if(in_current == MinoType::None)
	{
		currentType = nextType;
		nextType = in_next;
	}
	else
	{
		nextType = in_next;
		currentType = in_current;
	}

	color = Board::TetrominoColors[(int)currentType];

	for(int i = 0; i < 4; ++i)
	{
		figure.emplace_back(figuresList[(int)currentType][i]);
	}
}

// rotate the mino to the right if is not the O piece
// if collides, rotate back to the left
bool Tetromino::Rotate()
{
	if(currentType != MinoType::O)
	{
		RotateRight();

		if(this->CheckCollision())
		{
			RotateLeft();
		 	return false;
		}

		return true;
	}

	return false;
}

void Tetromino::MoveBy(const Location& offset_loc)
{
	assert(offset_loc.x >= -1 && offset_loc.x <= 1);
	assert(offset_loc.y >= -1 && offset_loc.y <= 1);

	loc.Add(offset_loc);
}

void Tetromino::DrawNextTetromino(int x, int y, int size)
{
	for(int i = 0; i < 4; ++i)
	{
		int x1 = (figuresList[(int)nextType][i].x * this->size) + x;
		int y1 = (figuresList[(int)nextType][i].y * this->size) + y;
		int spriteX = ((int)nextType) * this->size;

		DrawTextureRec(*texture, {(float)spriteX, 0, (float)this->size, (float)this->size}, {(float)x1, (float)y1}, WHITE);
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

bool Tetromino::CheckCollision()
{
	for(auto i = figure.begin(); i != figure.end(); ++i)
	{
		int x1 = i->x + loc.x;
		int y1 = i->y + loc.y;

		if(x1 >= 0 && x1 < board.tileWidth &&
			y1 >= 0 && y1 < board.tileHeight)
		{
			if(board.TileAt(x1, y1) > (int)Board::BlockType::Empty)
			{
				return true;
			}
		}
	}

	return false;
}

bool Tetromino::CanMoveX(int dx) const
{
	for(const auto& b : figure)
	{
		int x1 = b.x + loc.x + dx;
		int y1 = b.y + loc.y;

		if(x1 <= 0 || x1 >= board.tileWidth - 1)
		{
			return false;
		}
		else if(y1 >= 0 && board.TileAt(x1, y1) > (int)Board::BlockType::Empty)
		{
			return false;
		}
	}

	return true;
}

bool Tetromino::CanMoveY(int dy) const
{
	for(const auto& b : figure)
	{
		int x1 = b.x + loc.x;
		int y1 = b.y + loc.y + dy;

		if(y1 >= board.tileHeight - 1)
		{
			return false;
		}
		else if(y1 >= 0 && board.TileAt(x1, y1) > (int)Board::BlockType::Empty)
		{
			return false;
		}
	}

	return true;
}

int Tetromino::PutPieceOnBoard()
{
	for(auto i = figure.begin(); i != figure.end(); ++i)
	{
		int x1 = i->x + loc.x;
		int y1 = i->y + loc.y;

		if(x1 >= 0 && x1 < board.tileWidth &&
			y1 >= 0 && y1 < board.tileHeight)
		{
			board.SetTile(x1, y1, (int)currentType);
		}
	}

	return 0;
}

void Tetromino::GetNearestBottomCollision()
{
	for(int y = loc.y; y < board.tileHeight - 1; ++y)
	{
		for(const auto& b : figure)
		{
			int dy = y + b.y;
			int dx = b.x + loc.x;

			if(board.TileAt(dx, dy + 1) > (int)Board::BlockType::Empty)
			{
				nearestBottomCollision = y; //dy - loc.y - 1;
				return;
			}
		}
	}
}

// int Tetromino::DrawGhost()
// {
// 	int yOffset = board.tileHeight - 1;

// 	for(int yStart = loc.y; yStart < board.tileHeight; ++yStart)
// 	{
// 		for(const auto& f : figure)
// 		{
// 			int y1 = f.y + yStart;
// 			if(y1 >= 0)
// 			{
// 				if((y1 >= board.tileHeight) ||
// 				(board.TileAt(f.x + loc.x, f.y + yStart) >= 0))
// 				{
// 					return yStart - loc.y - 1;
// 				}
// 			}
// 		}
// 	}

// 	return board.tileHeight - 1 - loc.y;
// }