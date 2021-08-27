#include "tetromino.h"
#include <cassert>
#include <cmath>
#include <algorithm>

Tetromino::Tetromino(const Location& loc, int size, Board& board)
	:
	figure(4), loc(loc), initialLoc(loc), size(size), board(board)
{
	
}

void Tetromino::Draw()
{
	Location brdLoc = board.GetLocation();

	for(const auto& f : figure)
	{
		int x1 = f.x + loc.x + brdLoc.x;
		int y1 = f.y + loc.y + brdLoc.y;

		int spriteX = (int)currentType * size;
		int y2 = y1 * size;
		DrawTextureRec(*texture, {(float)spriteX, 0, (float)size, (float)size}, {(float)x1 * size, (float)y2}, WHITE);
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
		int spriteX = (int)currentType * size;
		//DrawRectangleLinesEx({(float)x1 * size + 1, (float)(yOffset + y1) * size + 1, (float)size - 1, (float)size - 1}, 1, Fade(MAROON, 0.5f));
		DrawTextureRec(*texture, {(float)spriteX, 0, (float)size, (float)size}, {(float)x1 * size, (float)(yOffset + y1) * size}, Fade(WHITE, 0.3f));
	}

}

void Tetromino::Init(MinoType in_type)
{
	texture = AssetManager::LoadSprite("resources/blocks.png");
	landed = false;

	figure.clear();

	loc = initialLoc;

	currentType = in_type;

	color = Board::TetrominoColors[(int)currentType];
	colorIndex = (int)currentType;

	for(int i = 0; i < 4; ++i)
	{
		figure.emplace_back(figuresList[(int)currentType][i]);
	}
}

bool Tetromino::Rotate()
{
	if(currentType != MinoType::O)
	{
		RotateRight();

		// CollisionType collide = CheckCollision();
		// if(collide.left == 1 || collide.right == 1 || collide.bottom == 1)
		// {
		// 	RotateLeft();
		// 	return false;
		// }

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

	if(this->CheckCollision())
	{
		if(offset_loc.x > 0) // collide right
		{
			loc.Add({-1, 0});
		}
		else if(offset_loc.x < 0) // collide left
		{
			loc.Add({1, 0});
		}
		else if(offset_loc.y) // collide bottom
		{
			landed = true;
			loc = tmp;
			return true;
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
		int spriteX = (int)nextType * size;

		//DrawRectangle(x1 + 1, y1 + 1, size - 1, size - 1, Board::TetrominoColors[(int)nextType]);
		DrawTextureRec(*texture, {(float)spriteX, 0, (float)size, (float)size}, {(float)x1, (float)y1}, WHITE);
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
		if(board.TileAt(i->x + loc.x, i->y + loc.y) > (int)Board::BlockType::Empty)
		{
			return true;
		}
	}

	return false;
}

void Tetromino::PutPieceOnBoard()
{
	for(const auto& f : figure)
	{
		board.SetTile(f.x + loc.x, f.y + loc.y, colorIndex);
	}

	board.CheckAndDeleteLines();
}

void Tetromino::CleanUp()
{
	UnloadTexture(*texture);
}

int Tetromino::DrawGhost()
{
	int yOffset = board.tileHeight - 1;

	for(int yStart = loc.y; yStart < board.tileHeight; ++yStart)
	{
		for(const auto& f : figure)
		{
			int y1 = f.y + yStart;
			if(y1 >= 0)
			{
				if((y1 >= board.tileHeight) ||
				(board.TileAt(f.x + loc.x, f.y + yStart) >= 0))
				{
					return yStart - loc.y - 1;
				}
			}
		}
	}

	return board.tileHeight - 1 - loc.y;
}