#include "gamestate.h"

GameState::GameState(GameDataRef data)
    :
    data(std::make_shared<GameData>()), board({0, 0}, cellSize, data), mainPiece({6, 0}, cellSize, board, data), minoDst(0, 6)
{
}

GameState::~GameState()
{
	data->assets.CleanUp();
	data->assets.MurderOrphans();
}

void GameState::Init()
{
	mainPiece.Init((Tetromino::MinoType)minoDst(rng), (Tetromino::MinoType)minoDst(rng));
	music = data->assets.LoadMusic("resources/tetrisbgm.mp3");
    
	SetMusicVolume(*music, 0.8f);
    PlayMusicStream(*music);

	moveSound = data->assets.LoadSound("resources/move.wav");
	rotateSound = data->assets.LoadSound("resources/rotate.wav");
	landSound = data->assets.LoadSound("resources/land.wav");
	lineSound = data->assets.LoadSound("resources/line.wav");
}

void GameState::Input()
{
    offset = {};

    if(IsKeyPressed(KEY_SPACE))
    {
        //currentState = States::Pause;
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
        if(mainPiece.Rotate())
        {
            PlaySound(*rotateSound);
        }
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
}

void GameState::Update(float dt)
{
	frameTime = dt;

    UpdateMusicStream(*music);

    board.Update();

    if(offset.x != 0)
    {
        if(mainPiece.CanMoveX(offset.x))
        {
            PlaySound(*moveSound);
            mainPiece.MoveBy({offset.x, 0});
        }
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
                PlaySound(*lineSound);
                //Score::GetReference().AddScore(delLines * (10 * delLines));
            }
            else
            {
                PlaySound(*landSound);
            }

            mainPiece.Init((Tetromino::MinoType)minoDst(rng));

            //currentState = States::Deleting;
        }
        else
        {
            //currentState = States::GameOver;
        }
    }
}

void GameState::Draw()
{
	std::string scoreText;
	std::string text;
	int textLenPixels = 0;

    board.DrawBorders();
    board.Draw();
    //mainPiece.DrawG();
    mainPiece.Draw();

    DrawText("HIGH SCORE", 420, 0, 30, RAYWHITE);
    // scoreText = std::to_string(Score::GetReference().GetHighScore());
    // DrawText(scoreText.c_str(), 420, 30, 25, MAROON);
    DrawText("Score", 420, 60, 30, RAYWHITE);
    // scoreText = std::to_string(Score::GetReference().GetCurrentScore());
    // DrawText(scoreText.c_str(), 420, 90, 20, GOLD);


    DrawText("Next tetromino", 450, 160, 20, RAYWHITE);
    mainPiece.DrawNextTetromino(500, 190, 30);

    DrawFPS(GetScreenWidth() - 80, GetScreenHeight() - 30);
    DrawText("VitalZero's Petris - VZ Studio 2021.", 10, GetScreenHeight() - 30, 20, RAYWHITE);
}