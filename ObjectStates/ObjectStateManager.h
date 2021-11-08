#pragma once
#include "IObjectState.h"
#include <cassert>

template <class T>
class ObjectStateManager
{
private:
    T* owner;
    IObjectStsate<T>* curState;
    IObjectStsate<T>* prevState;

public:
    ObjectStateManager(T* owner)
        :
        owner(owner), curState(nullptr), prevState(nullptr)
    {}

    void SetCurrentState(IObjectStsate<T>* state) { curState = state; }
    void SetPreviousState(IObjectStsate<T>* state) { prevState = state; }
    void Input(float dt) const 
    {
        if(curState)
        {
            curState->Input(owner);
        }
    }
    void Update(float dt) const 
    {
        if(curState)
        {
            curState->Update(owner, dt);
        }
    }
    void Draw() const 
    {
        if(curState)
        {
            curState->Draw(owner);
        }
    }
    void ChangeState(IObjectStsate<T>* state)
    {
        assert(state && "<StateMachine::ChangeState>: trying to change to a null state");

        prevState = curState;
        curState->Exit(owner);
        curState = state;
        curState->Enter(owner);
    }
    void RevertToPrevious(IObjectStsate<T>* state)
    {
        ChangeState(prevState);
    }
    IObjectStsate<T>* CurrentState() const { return curState; }
    IObjectStsate<T>* PreviousState() const { return prevState; }
    bool IsInState(const IObjectStsate<T>& state) const;
};