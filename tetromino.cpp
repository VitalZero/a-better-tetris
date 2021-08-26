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

		//DrawRectangle(x1 * size + 1, y1 * size + 1, size - 1, size - 1, color);
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

		CollisionType collide = CheckCollision();
		if(collide.left == 1 || collide.right == 1 || collide.bottom == 1)
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

	CollisionType collide = CheckCollision();
	if(collide.right)
	{
		loc.Add({collide.right, 0});

		return false;
	}
	else if(collide.left)
	{
		loc.Add({-collide.left, 0});

		return false;
	}
	if(collide.bottom)
	{
		if(offset_loc.y > 0)
		{
			loc = tmp;
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

CollisionType Tetromino::CheckCollision()
{
	for(const auto& block : figure)
	{
		int x1 = block.x + loc.x;
		int y1 = block.y + loc.y;

		if(x1 >= board.tileWidth)
			return { 0, -1, 0 };
		else if(x1 < 0)
			return { 1, 0, 0 };
			
		if(y1 >= 0)
		{
			if((y1 >= board.tileHeight) ||
			(board.TileAt(x1, y1) >= 0))
			return { 0, 0, 1 };
		}
	}

	return { 0, 0, 0 };
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