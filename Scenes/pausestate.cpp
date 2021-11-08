#include "pausestate.h"
#include "gamestate.h"

PauseState::PauseState(GameDataRef data, GameState& gameState)
    :
    data(data), gameState(gameState)
{

}

PauseState::~PauseState()
{
}

void PauseState::Init()
{
}

void PauseState::Input()
{
    if(IsKeyPressed(KEY_SPACE))
    {
        data->states.RemoveState();
    }
}

void PauseState::Update(float dt)
{

}

void PauseState::Draw()
{
    gameState.Draw();
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5F));
    DrawText("Paused!", 300, 300, 40, RAYWHITE);
}