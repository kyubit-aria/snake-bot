#include "GreedySnake.h"
#include <iostream>

GreedySnake::GreedySnake(SnakeState initial_state) :
	observed_state(initial_state)
{}

SnakeState::Movement GreedySnake::decideAction()
{
	return greedyDeathAvoid();
}

void GreedySnake::setState(SnakeState state)
{
	this->observed_state = state;
}

bool GreedySnake::isLegal(SnakeState::Movement action)
{
	SnakeState::Elements observation;
	switch (action)
	{
	case SnakeState::UP:
		observation = (SnakeState::Elements) observed_state.observePoint(SnakeState::SnakeObservation::ABOVE);
		return elememtMovable(observation);
	case SnakeState::DOWN:
		observation = (SnakeState::Elements) observed_state.observePoint(SnakeState::SnakeObservation::BELOW);
		return elememtMovable(observation);
	case SnakeState::LEFT:
		observation = (SnakeState::Elements) observed_state.observePoint(SnakeState::SnakeObservation::TO_LEFT);
		return elememtMovable(observation);
	case SnakeState::RIGHT:
		observation = (SnakeState::Elements) observed_state.observePoint(SnakeState::SnakeObservation::TO_RIGHT);
		return elememtMovable(observation);
	}
}

bool GreedySnake::elememtMovable(SnakeState::Elements observation)
{
	return (observation == SnakeState::Elements::EMPTY) || observation == SnakeState::Elements::FRUIT;
}

int GreedySnake::evaluateMove(SnakeState::Movement action)
{
	if (!isLegal(action)) return 10;

	int vertical_difference = getVerticalDifference();
	int horizontal_difference = getHorizontalDifference();

	switch (action)
	{
	case SnakeState::UP:
		return abs(vertical_difference) - abs(vertical_difference - 1);
	case SnakeState::DOWN:
		return abs(vertical_difference) - abs(vertical_difference + 1);
		break;
	case SnakeState::LEFT:
		return abs(horizontal_difference) - abs(horizontal_difference + 1);
	case SnakeState::RIGHT:
		return abs(horizontal_difference) - abs(horizontal_difference - 1);
	}
	
	
}

int GreedySnake::getVerticalDifference()
{
	int fruit_vertical_pos
		= observed_state.observePoint(SnakeState::SnakeObservation::FRUIT_VERTICAL);
	int snake_vertical_pos
		= observed_state.observePoint(SnakeState::SnakeObservation::SNAKE_VERTICAL);

	return fruit_vertical_pos - snake_vertical_pos;
}

int GreedySnake::getHorizontalDifference()
{
	int fruit_horizontal_pos
		= observed_state.observePoint(SnakeState::SnakeObservation::FRUIT_HORIZONTAL);
	int snake_horizontal_pos
		= observed_state.observePoint(SnakeState::SnakeObservation::SNAKE_HORIZONTAL);
	return fruit_horizontal_pos - snake_horizontal_pos;
}


SnakeState::Movement GreedySnake::greediestMove()
{
	int vertical_difference = getVerticalDifference();
	int horizontal_difference = getHorizontalDifference();
	
	if (abs(vertical_difference) > abs(horizontal_difference))
	{
		if (vertical_difference > 0) return SnakeState::Movement::UP;
		if (vertical_difference < 0) return SnakeState::Movement::DOWN;
	}

	if (horizontal_difference > 0) return SnakeState::Movement::RIGHT;
	else return SnakeState::Movement::LEFT;
}

SnakeState::Movement GreedySnake::greedyDeathAvoid()
{
	SnakeState::Movement potential_move = greediestMove();

	if (isLegal(potential_move))
	{
		return SnakeState::Movement(potential_move);
	}

	int up_eval = evaluateMove(SnakeState::Movement::UP);
	int down_eval = evaluateMove(SnakeState::Movement::DOWN);
	int right_eval = evaluateMove(SnakeState::Movement::RIGHT);
	int left_eval = evaluateMove(SnakeState::Movement::LEFT);



	if (up_eval != 10) return SnakeState::Movement::UP;
	if (down_eval != 10)return SnakeState::Movement::DOWN;
	if (right_eval != 10)return SnakeState::Movement::RIGHT;
	if (left_eval != 10)return SnakeState::Movement::LEFT;
}
