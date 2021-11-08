#pragma once
#include "Istate.h"
#include "../gamedata.h"

class MainScreenState : public IState
{
public:
    MainScreenState(GameDataRef data);
    ~MainScreenState();
    void Init() override;
    void Input() override;
    void Update(float dt) override;
    void Draw() override;

private:
    GameDataRef data;
};
