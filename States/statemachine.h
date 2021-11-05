#pragma once

#include <memory>
#include <stack>
#include "Istate.h"

using StateRef = std::unique_ptr<IState>;

class StateMachine
{
public:
	StateMachine() = default;
	~StateMachine() = default;

	void AddState(StateRef newState, bool isReplacing = true);
	void RemoveState();
	void ProcessStateChanges();
	StateRef& GetActiveState();

private:
	std::stack<StateRef> states;
	StateRef newState;
	bool isAdding;
	bool isRemoving;
	bool isReplacing;
};
