#include "BoardPlayingState.h"
#include "board.h"

void BoardPlayingState::Enter(Board* owner)
{
	owner->Init();
}

void BoardPlayingState::Input(Board* owner)
{}

void BoardPlayingState::Update(Board* owner, float dt)
{
	owner->Update(dt);
}
void BoardPlayingState::Draw(Board* owner)
{
	owner->Draw();
}
void BoardPlayingState::Exit(Board* owner)
{}