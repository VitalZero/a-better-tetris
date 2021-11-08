#pragma once
#include "ObjectStates/IObjectState.h"

class Board;

class BoardDeletingState : public IObjectStsate<Board>
{
    void Enter(Board* owner) override;
    void Input(Board* owner ) override;
    void Update(Board* owner, float) override;
    void Draw(Board* owner) override;
    void Exit(Board* owner) override;
};