#pragma once
#include "SnakeAgent.h"

class GreedySnake : public SnakeAgent
{
public:
	GreedySnake(SnakeState);

	void setState(SnakeState);
	SnakeState::Movement decideAction();

private:

	bool isLegal(SnakeState::Movement);
	bool elememtMovable(SnakeState::Elements);

	int evaluateMove(SnakeState::Movement);
	int getVerticalDifference();
	int getHorizontalDifference();
	SnakeState::Movement greediestMove();
	SnakeState::Movement greedyDeathAvoid();

	SnakeState observed_state;
};

