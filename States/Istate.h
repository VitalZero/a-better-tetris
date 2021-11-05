#pragma once

class IState
{
public:
    virtual void Init() = 0;
    virtual void Input() = 0;
    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;
    virtual void Pause() {}
    virtual void Resume() {}
};