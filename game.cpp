#pragma once
#include "game.h"
#include <raylib.h>

Game::Game(int x, int y, const std::string& title)
	:
	board({0, 0}, cellSize), mainPiece({6, 0}, cellSize, board), nextPiece(16, 3, cellSize, board)
{
	InitWindow(x, y, title.c_str());
	SetTargetFPS(60);

	target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
	shader = LoadShader(0, TextFormat("bloom.fs", 330));
}

void Game::Run()
{
	while(!WindowShouldClose())
	{
		Update();
		
		BeginTextureMode(target);
		ClearBackground(Fade(BLACK, 0.0f));
			board.Draw();
			mainPiece.DrawG();
		EndTextureMode();

		BeginDrawing();
		ClearBackground(BLACK);
		Draw();
		EndDrawing();
	}

	UnloadRenderTexture(target); 
	UnloadShader(shader);
	CloseWindow();
}

void Game::Update()
{
	Location offset = {};

	if(IsKeyPressed(KEY_SPACE))
	{
		mainPiece.Reset();
	}
	
	if(IsKeyPressed(KEY_RIGHT))
	{
		offset = {1, 0};
	}
	else if(IsKeyPressed(KEY_LEFT))
	{
		offset = {-1, 0};
	}
	
	if(IsKeyPressed(KEY_UP))
	{
		mainPiece.Rotate();
	}

	if(IsKeyDown(KEY_DOWN) && (mainPiece.GetLocation().y > 0))
		moveCounter += 40;
	else
		++moveCounter;
	
	if(moveCounter >= movePeriod)
	{
		moveCounter = 0;
		offset.y = 1;
	}

	mainPiece.MoveBy(offset);
}

void Game::Draw()
{
	board.DrawBorders();

	BeginShaderMode(shader);
	DrawTextureRec(target.texture, {0, 0, (float)target.texture.width, (float)-target.texture.height }, {0, 0}, WHITE);
	EndShaderMode();
	
	mainPiece.Draw();
	//nextPiece.Draw();

	DrawFPS(GetScreenWidth() - 80, 20);
}