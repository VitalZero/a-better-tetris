#pragma once
#include "Istate.h"
#include "../gamedata.h"

class GameOverState : public IState
{
public:
    GameOverState(GameDataRef data);
    ~GameOverState();
    void Init() override;
    void Input() override;
    void Update(float dt) override;
    void Draw() override;

private:
    GameDataRef data;
};
