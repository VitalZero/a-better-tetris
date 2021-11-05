#include "statemachine.h"

void StateMachine::AddState(StateRef newState, bool isReplacing)
{
	isAdding = true;
	this->isReplacing = isReplacing;

	this->newState = std::move(newState);
}

void StateMachine::RemoveState()
{
	isRemoving = true;
}

void StateMachine::ProcessStateChanges()
{
	if (isRemoving && !states.empty())
	{
		states.pop();

		if (!states.empty())
		{
			states.top()->Resume();
		}
	}

	isRemoving = false;

	if (isAdding)
	{
		if (!states.empty())
		{
			if (isReplacing)
			{
				states.pop();
			}
			else
			{
				states.top()->Pause();
			}
		}

		states.push(std::move(newState));
		states.top()->Init();
		isAdding = false;
	}
}

StateRef& StateMachine::GetActiveState()
{
	return states.top();
}
