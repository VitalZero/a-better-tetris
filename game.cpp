#include "game.h"
#include "assetmanager.h"
#include "score.h"
#include "States/mainscreenstate.h"

Game::Game()
{
	data->states.AddState(std::make_unique<MainScreenState>(data));
}

Game::~Game()
{
	data->assets.CleanUp();
}

void Game::Run()
{
	while(!WindowShouldClose())
	{
		data->states.ProcessStateChanges();

		Input();
		Update(GetFrameTime());
		BeginDrawing();
		ClearBackground(BLACK);
		Draw();
		EndDrawing();
	}
}

void Game::Input()
{
	data->states.GetActiveState()->Input();
}

void Game::Update(float dt)
{
	data->states.GetActiveState()->Update(dt);
}

void Game::Draw()
{
	data->states.GetActiveState()->Draw();
}