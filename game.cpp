#include "game.h"
#include "assetmanager.h"
#include "score.h"

Game::Game()
	:
	board({0, 0}, cellSize), mainPiece({6, 0}, cellSize, board), minoDst(0, 6), currentState(States::StartScreen)
{
	mainPiece.Init((Tetromino::MinoType)minoDst(rng), (Tetromino::MinoType)minoDst(rng));
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
		Input();
		Update();
		BeginDrawing();
		ClearBackground(BLACK);
		Draw();
		EndDrawing();
	}
}

void Game::Input()
{

	offset = {};
	
	switch(currentState)
	{
		// Start Screen State
		case States::StartScreen:

			if(IsKeyPressed(KEY_ENTER))
			{
				currentState = States::Game;
			}

		break;

		// Game state
		case States::Game:

			if(IsKeyPressed(KEY_SPACE))
			{
				currentState = States::Pause;
			}

			if(IsKeyDown(KEY_RIGHT))
			{
				if(lateralCounter >= lateralCounterPeriod)
				{
					offset = {1, 0};
					lateralCounter = 0;
				}
			}
			else if(IsKeyDown(KEY_LEFT))
			{
				if(lateralCounter >= lateralCounterPeriod)
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
		break;

		// Pause State
		case States::Pause:

			if(IsKeyPressed(KEY_SPACE))
			{
				currentState = States::Game;
			}

		break;

		// Game Over State
		case States::GameOver:

			if(IsKeyPressed(KEY_ENTER))
			{
				currentState = States::Game;
			}
			
		break;

	}
}

void Game::Update()
{
	switch(currentState)
	{
		// Start Screen State
		case States::StartScreen:

			++secTimer;

			if(secTimer >= 60)
			{
				secTimer = 0;
			}

		break;

		// Game state
		case States::Game:

			board.Update();
			
			if(mainPiece.CanMoveX(offset.x))
			{
				mainPiece.MoveBy({offset.x, 0});
			}

			if(mainPiece.CanMoveY(offset.y))
			{
				mainPiece.MoveBy({0, offset.y});
			}
			else
			{
				if(mainPiece.GetLocation().y > 0)
				{
					mainPiece.PutPieceOnBoard();

					int delLines = board.CheckAndMarkLines();

					if(delLines > 0)
					{
						Score::GetReference().AddScore(delLines * (10 * delLines));
					}
					mainPiece.Init((Tetromino::MinoType)minoDst(rng));

					currentState = States::Deleting;
				}
				else
				{
					currentState = States::GameOver;
				}
			}

		// Pause State
		case States::Pause:
		break;

		// Deleting State
		case States::Deleting:
		
			board.Update();

			if(!board.IsDeleting())
			{
				currentState = States::Game;
			}

		break;

		// Game Over State
		case States::GameOver:
			mainPiece.Init((Tetromino::MinoType)minoDst(rng));
			board.Init();
			moveCounter = 0;
			Score::GetReference().ResetScore();
		break;
	}
}

void Game::Draw()
{
	std::string scoreText;
	std::string text;
	int textLenPixels = 0;
	
	switch(currentState)
	{
		// Start Screen State
		case States::StartScreen:
		{
			text = "VZ's PETRIS";
			textLenPixels = MeasureText(text.c_str(), 60);
			DrawText(text.c_str(), GetScreenWidth() / 2 - textLenPixels / 2, 200, 60, RAYWHITE);

			text = "Press ENTER to start";
			textLenPixels = MeasureText(text.c_str(), 40);

			if(secTimer % 30 < 15)
			{
				DrawText(text.c_str(), GetScreenWidth() / 2 - textLenPixels / 2, (GetScreenHeight() / 2 - 20) + 40, 40, RAYWHITE);
			}
		}
		break;

		// Game state
		case States::Game:
		{
			board.DrawBorders();
			board.Draw();
			//mainPiece.DrawG();
			mainPiece.Draw();

			DrawText("HIGH SCORE", 420, 0, 30, RAYWHITE);
			scoreText = std::to_string(Score::GetReference().GetHighScore());
			DrawText(scoreText.c_str(), 420, 30, 25, MAROON);
			DrawText("Score", 420, 60, 30, RAYWHITE);
			scoreText = std::to_string(Score::GetReference().GetCurrentScore());
			DrawText(scoreText.c_str(), 420, 90, 20, GOLD);

			
			DrawText("Next tetromino", 450, 160, 20, RAYWHITE);
			mainPiece.DrawNextTetromino(500, 190, 30);

			DrawFPS(GetScreenWidth() - 80, GetScreenHeight() - 30);
			DrawText("VitalZero's Petris - VZ Studio 2021.", 10, GetScreenHeight() - 30, 20, RAYWHITE);
		}
		break;

		case States::Deleting:
		{
			board.DrawBorders();
			board.Draw();
			//mainPiece.DrawG();

			DrawText("HIGH SCORE", 420, 0, 30, RAYWHITE);
			scoreText = std::to_string(Score::GetReference().GetHighScore());
			DrawText(scoreText.c_str(), 420, 30, 25, MAROON);
			DrawText("Score", 420, 60, 30, RAYWHITE);
			scoreText = std::to_string(Score::GetReference().GetCurrentScore());
			DrawText(scoreText.c_str(), 420, 90, 20, GOLD);
			
			DrawText("Next tetromino", 450, 160, 20, RAYWHITE);
			mainPiece.DrawNextTetromino(500, 190, 30);

			DrawFPS(GetScreenWidth() - 80, GetScreenHeight() - 30);
			DrawText("VitalZero's Petris - VZ Studio 2021.", 10, GetScreenHeight() - 30, 20, RAYWHITE);
		}
		break;

		// Pause State
		case States::Pause:
		{
			board.DrawBorders();
			board.Draw();

			DrawFPS(GetScreenWidth() - 80, GetScreenHeight() - 30);
			DrawText("VitalZero's Petris - VZ Studio 2021.", 10, GetScreenHeight() - 30, 20, RAYWHITE);

			text = "Paused";
			textLenPixels = MeasureText(text.c_str(), 40);
			DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.4));
			DrawText(text.c_str(), GetScreenWidth() / 2 - textLenPixels / 2, GetScreenHeight() / 2 - 20, 40, RAYWHITE);
		}
		break;

		// Game Over State
		case States::GameOver:
		{
			text = "Game Over";
			textLenPixels = MeasureText(text.c_str(), 40);
			DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.4));
			DrawText(text.c_str(), GetScreenWidth() / 2 - textLenPixels / 2, GetScreenHeight() / 2 - 20, 40, RAYWHITE);

			text = "Press Enter to play again";
			textLenPixels = MeasureText(text.c_str(), 30);
			DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.4));
			DrawText(text.c_str(), GetScreenWidth() / 2 - textLenPixels / 2, (GetScreenHeight() / 2 - 20) + 40, 30, RAYWHITE);
		}
		break;
	}	
}