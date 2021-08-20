#include "game.h"

Game::Game(int x, int y, const std::string& title)
	:
	board({0, 0}, cellSize), mainPiece({6, 0}, cellSize, board), minoDst(0, 6)
{
	InitWindow(x, y, title.c_str());
	SetTargetFPS(60);

	tetrominoTexture = LoadTexture("resources/blocks.png");
	mainPiece.SetTextureReference(&tetrominoTexture);
	board.SetTextureReference(&tetrominoTexture);

	mainPiece.Init((Tetromino::MinoType)minoDst(rng));
	mainPiece.SetNext((Tetromino::MinoType)minoDst(rng));
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

	UnloadTexture(tetrominoTexture);
	CloseWindow();
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
	mainPiece.DrawG();
	mainPiece.Draw();

	DrawText("Next tetromino", 450, 70, 20, RAYWHITE);
	mainPiece.DrawNextTetromino(500, 100, 30);

	DrawFPS(GetScreenWidth() - 80, GetScreenHeight() - 30);
	DrawText("VitalZero's Petris - VZ Studio 2021.", 10, GetScreenHeight() - 30, 20, RAYWHITE);
}