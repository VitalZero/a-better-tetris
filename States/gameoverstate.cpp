#include "gameoverstate.h"
#include "mainscreenstate.h"

GameOverState::GameOverState(GameDataRef data)
    :
    data(data)
{
    
}

GameOverState::~GameOverState()
{
    
}

void GameOverState::Init() 
{
    
}

void GameOverState::Input() 
{
    if(IsKeyPressed(KEY_ENTER))
    {
        data->states.AddState(std::make_unique<MainScreenState>(data));
    }
}

void GameOverState::Update(float dt) 
{
    
}

void GameOverState::Draw() 
{
    DrawText("Game Over!!", 200, 260, 60, RAYWHITE);
    DrawText("Press Enter to go to main screen", 50, 320, 30, RAYWHITE);
}

