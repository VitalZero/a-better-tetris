#include "game.h"
#include "assetmanager.h"

Game::Game()
	:
	board({0, 0}, cellSize), mainPiece({6, 0}, cellSize, board), minoDst(0, 6)
{
	mainPiece.Init((Tetromino::MinoType)minoDst(rng));
	mainPiece.SetNext((Tetromino::MinoType)minoDst(rng));
}

Game::~Game()
{
	AssetManager::CleanUp();
	AssetManager::MurderOrphans();
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
}

void Game::Update()
{
	Location offset = {};

	if(IsKeyPressed(KEY_SPACE))
	{
		mainPiece.Init((Tetromino::MinoType)1);
	}
	
	if(IsKeyDown(KEY_RIGHT))
	{
		if(lateralCounter >= 7)
		{
			offset = {1, 0};
			lateralCounter = 0;
		}
	}
	else if(IsKeyDown(KEY_LEFT))
	{
		if(lateralCounter >= 7)
		{
			offset = {-1, 0};
			lateralCounter = 0;
		}
	}
	
	if(IsKeyPressed(KEY_UP))
	{
		mainPiece.Rotate();
	}

	if(IsKeyDown(KEY_DOWN) && (mainPiece.GetLocation().y > 0))
		moveCounter += 40;
	else
		++moveCounter;

	++lateralCounter;
	
	if(moveCounter >= movePeriod)
	{
		moveCounter = 0;
		offset.y = 1;
	}

	mainPiece.MoveBy(offset);

	if(mainPiece.IsLanded())
	{
		mainPiece.PutPieceOnBoard();
		mainPiece.Init(mainPiece.GetNext());
		mainPiece.SetNext((Tetromino::MinoType)minoDst(rng));
	}
}

void Game::Draw()
{
	board.DrawBorders();
	board.Draw();
	//mainPiece.DrawG();
	mainPiece.Draw();

	DrawText("HIGH SCORE", 420, 0, 30, RAYWHITE);
	DrawText("123456789", 420, 30, 25, MAROON);
	DrawText("Score", 420, 60, 30, RAYWHITE);
	DrawText("100", 420, 90, 20, GOLD);

	
	DrawText("Next tetromino", 450, 160, 20, RAYWHITE);
	mainPiece.DrawNextTetromino(500, 190, 30);

	DrawFPS(GetScreenWidth() - 80, GetScreenHeight() - 30);
	DrawText("VitalZero's Petris - VZ Studio 2021.", 10, GetScreenHeight() - 30, 20, RAYWHITE);
}