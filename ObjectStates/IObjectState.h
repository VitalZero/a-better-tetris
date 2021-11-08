#pragma once

template <class T>
class IObjectStsate
{
public:
    virtual ~IObjectStsate(){}
    virtual void Enter(T*) = 0;
    virtual void Input(T*) = 0;
    virtual void Update(T*, float) = 0;
    virtual void Draw(T*) = 0;
    virtual void Exit(T*) = 0;
};