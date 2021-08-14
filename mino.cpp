#include "mino.h"

void Mino::Init(const Location& in_loc, int in_size, MinoType in_minoType)
{
	loc = in_loc;
	size = in_size;
	type = in_minoType;

	for(int i = 0; i < 4; ++i)
	{
		figure.emplace_back(minoList[(int)type][i]);
	}
}

void Mino::Draw()
{
	for(const auto& block : figure)
	{
		int x1 = loc.x + block.x;
		int y1 = loc.y + block.y;

		DrawRectangle(x1 * size + 1, y1 * size + 1, size - 1, size - 1, colors[(int)type]);
	}
}