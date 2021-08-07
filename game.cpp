#pragma once
#include "game.h"
#include <raylib.h>

Game::Game(int x, int y, const std::string& title)
	:
	board({0, 0}, cellSize), mainPiece({6, 0}, cellSize, board), nextPiece(16, 3, cellSize, board)
{
	InitWindow(x, y, title.c_str());
	SetTargetFPS(60);
}

void Game::Run()
{
	while(!WindowShouldClose())
	{
		Update();
		BeginDrawing();
		ClearBackground(BLACK);
		Draw();
		EndDrawing();
	}

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

	if(IsKeyDown(KEY_DOWN))
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
	board.Draw();
	mainPiece.Draw();
	//nextPiece.Draw();

	DrawFPS(GetScreenWidth() - 80, 20);
}