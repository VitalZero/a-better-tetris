#include "game.h"

class App
{
public:
	App(int x, int y, const std::string& title)
	{
		SetTargetFPS(60);
		InitWindow(x, y, title.c_str());
		InitAudioDevice();

		Game game;
		game.Run();
	}
	~App()
	{
		CloseWindow();
		CloseAudioDevice();
	}
	
	App(const App&) = delete;
	App(const App&&) = delete;
	App operator= (const App&) = delete;
	App& operator= (const App&&) = delete;
};