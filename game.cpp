#pragma once
#include "game.h"

Game::Game(int x, int y, const std::string& title)
	:
	board({0, 0}, cellSize), mainPiece({6, 0}, cellSize, board), nextPiece(16, 3, cellSize, board)
{
	InitWindow(x, y, title.c_str());
	SetTargetFPS(60);

	target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
	shader = LoadShader(0, TextFormat("bloom.fs", 330));
	bgm = LoadMusicStream("resources/tetrisbgm.mp3");
	moveSound = LoadSound("resources/move.wav");
	lockSound = LoadSound("resources/lock.wav");
	rotateSound = LoadSound("resources/rotate.wav");
	SetSoundVolume(moveSound, 0.3f);
	SetSoundVolume(rotateSound, 0.3f);
	SetSoundVolume(lockSound, 0.3f);

	SetMusicVolume(bgm, 0.2f);
	PlayMusicStream(bgm);
}

void Game::Run()
{
	while(!WindowShouldClose())
	{
		UpdateMusicStream(bgm);
		
		Update();
		
		BeginTextureMode(target);
		ClearBackground(Fade(BLACK, 0.0f));
			//board.DrawBorders();
			board.Draw();
			mainPiece.DrawG();
			mainPiece.Draw();
		EndTextureMode();

		BeginDrawing();
		ClearBackground(BLACK);
		Draw();
		EndDrawing();
	}

	UnloadRenderTexture(target); 
	UnloadShader(shader);
	UnloadMusicStream(bgm);
	UnloadSound(moveSound);
	UnloadSound(lockSound);
	UnloadSound(rotateSound);
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
		PlaySound(moveSound);
	}
	else if(IsKeyPressed(KEY_LEFT))
	{
		offset = {-1, 0};
		PlaySound(moveSound);
	}
	
	if(IsKeyPressed(KEY_UP))
	{
		if(mainPiece.Rotate())
			PlaySound(rotateSound);
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

	if(mainPiece.MoveBy(offset))
		PlaySound(lockSound);

}

void Game::Draw()
{
	board.DrawBorders();

	BeginShaderMode(shader);
	DrawTextureRec(target.texture, {0, 0, (float)target.texture.width, (float)-target.texture.height }, {0, 0}, Fade(WHITE, 0.0));
	EndShaderMode();
	
	
	//mainPiece.Draw();
	//nextPiece.Draw();

	DrawFPS(GetScreenWidth() - 80, 20);
	DrawText("VitalZero's Petris - VZ Studio 2021.", 10, GetScreenHeight() - 30, 20, RAYWHITE);
}