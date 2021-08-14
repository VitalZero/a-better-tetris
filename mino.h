#include <vector>
#include "location.h"
#include <raylib.h>

class Mino
{
public:
	enum class MinoType { None = -1, S, T, O, L, J, Z, I };

private:
	struct Block
	{
		int x;
		int y;
	};

public:
	Mino() = default;
	void Init(const Location& in_loc, int in_size, MinoType in_minoType);
	void Draw();
	
private:
	std::vector<Block> figure;
	Location loc;
	int size;
	MinoType type;
	static constexpr Block minoList[7][4]= 
	{
		{ {0, 0}, {1, 0},  {-1, 1},  {0, 1} }, // S
		{ {0, 0}, {-1, 0},  {1, 0}, {0, 1} }, // T
		{ {0, 0},  {1, 0},  {0, 1},  {1, 1} }, // O
		{ {0, 0}, {-1, 0},  {1, 0},  {-1, 1} }, // L
		{ {0, 0}, {-1, 0},  {1, 0},  {1, 1} }, // J
		{ {0, 0}, {-1, 0}, {0, 1},  {1, 1} },// Z
		{ {0, 0}, {-1, 0},  {1, 0},  {2, 0} }  // I
	};
	static constexpr Color colors[7] =
	{
		RAYWHITE, RAYWHITE, RAYWHITE, RAYWHITE, RAYWHITE, RAYWHITE, RAYWHITE
	};
};