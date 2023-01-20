#pragma once
#include "SnakeState.h"

class GreedySnake
{
public:
	GreedySnake(SnakeState);
	SnakeState::Movement decideAction();
	void updateState(SnakeState);

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

