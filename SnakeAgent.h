#pragma once
#include "SnakeState.h"
class SnakeAgent
{
public:
	virtual void setState(SnakeState) = 0;
	virtual SnakeState::Movement decideAction() = 0;
};

