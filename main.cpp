#include "game.h"

int main()
{
	InitAudioDevice();
	Game game(640, 720, "Raylib Tetris test");
	game.Run();
	CloseAudioDevice();
	return 0;
}