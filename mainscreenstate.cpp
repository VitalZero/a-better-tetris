#include "mainscreenstate.h"
#include "gamestate.h"

MainScreenState::MainScreenState(GameDataRef data)
    : 
    data(data)
{
    
}

MainScreenState::~MainScreenState()
{
    
}

void MainScreenState::Init() 
{
    
}

void MainScreenState::Input() 
{
    if(IsKeyPressed(KEY_ENTER))
    {
        data->states.AddState(std::make_unique<GameState>(data));
    }
}

void MainScreenState::Update(float dt) 
{
    
}

void MainScreenState::Draw() 
{
    DrawText("VZ's Petris", 200, 300, 50, RAYWHITE);
}
