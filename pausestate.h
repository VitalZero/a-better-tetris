#pragma once
#include "Istate.h"
#include "gamedata.h"

class GameState;

class PauseState : public IState
{
public:
    PauseState(GameDataRef data, GameState& gameState);
    ~PauseState();
    void Init() override;
    void Input() override;
    void Update(float dt) override;
    void Draw() override;

private:
    GameDataRef data;
    GameState& gameState;
};