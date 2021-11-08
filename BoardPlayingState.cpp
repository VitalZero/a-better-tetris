#include "BoardPlayingState.h"
#include "board.h"

void BoardPlayingState::Enter(Board* owner)
{
	for(int y = 0; y < owner->tileHeight; ++y)
	{
		for(int x = 0; x < owner->tileWidth; ++x)
		{
			if(x == 0 || x == owner->tileWidth - 1 || y == owner->tileHeight - 1)
			{
				owner->grid[y * owner->tileWidth + x] = (int)Board::BlockType::Wall;
			}
			else
			{
				owner->grid[y * owner->tileWidth + x] = (int)Board::BlockType::Empty;
			}
		}
	}

	owner->Init();
}

void BoardPlayingState::Input(Board* owner)
{}
void BoardPlayingState::Update(Board* owner, float dt)
{
	owner->frameAccumulator += dt;

	if(owner->frameAccumulator >= 1.0f / 60.0f)
	{
		if(owner->deleting)
		{
			++owner->drawTimer;

			if(owner->drawTimer >= 40)
			{
				owner->deleting = false;
				owner->DeleteLines();
				owner->drawTimer = 0.0f;
			}
		}

		owner->frameAccumulator = 0.0f;
	}
}
void BoardPlayingState::Draw(Board* owner)
{
	for(int y = 0; y < owner->tileHeight; ++y)
	{
		for(int x = 0; x < owner->tileWidth; ++x)
		{
			int x1 = (x * owner->tileSize) + (owner->loc.x * owner->tileSize);
			int y1 = (y * owner->tileSize) + (owner->loc.y * owner->tileSize);

			int size = owner->tileSize;

			int tileValue = owner->TileAt(x, y);
			assert(tileValue < 7 || tileValue == (int)Board::BlockType::Wall);
			int spriteX = (tileValue) * owner->tileSize;

			if(tileValue > (int)Board::BlockType::Empty && tileValue != (int)Board::BlockType::Wall)
			{
				DrawTextureRec(*(owner->texture), {(float)spriteX, 0, (float)owner->tileSize, (float)owner->tileSize}, {(float)x1, (float)y1}, WHITE);
			}
			
			// else if(tileValue == (int)BlockType::Wall)	// dont draw the wall at the moment
			// {
			// 	DrawRectangle(x1, y1, tileSize, tileSize, DARKGRAY);
			// }
		}
	}

	if(owner->deleting)
	{
		Color c;
		if(owner->drawTimer % 10 < 5)
			c = Fade(RAYWHITE, 0.5f);
		else
			c = Fade(MAROON, 0.5f);

		for(const auto& b : owner->linesToDelete)
		{
			for(int x = 1; x < owner->tileWidth - 1; ++x)
			{
				int x1 = (x * owner->tileSize) + (owner->loc.x * owner->tileSize);
				int y1 = (b * owner->tileSize) + (owner->loc.y * owner->tileSize);
			//if(x > 0 && x < tileWidth - 1)
				DrawRectangle(x1, y1, owner->tileSize, owner->tileSize, c);
			}
		}
	}
}
void BoardPlayingState::Exit(Board* owner)
{}