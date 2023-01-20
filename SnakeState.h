#pragma once
struct SnakeState
{
	enum Elements
	{
		SNAKE,
		FRUIT,
		EMPTY,
		WALL
	};

	enum GameState
	{
		INVALID,
		READY,
		RUNNING,
		DIED,
		STOPPED
	};

	enum Movement
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	enum SnakeObservation
	{
		BOTTOM_LEFT,
		BELOW,
		BOTTOM_RIGHT,
		TO_LEFT,
		TO_RIGHT,
		TOP_LEFT,
		ABOVE,
		TOP_RIGHT,
		FRUIT_VERTICAL,
		FRUIT_HORIZONTAL,
		SNAKE_VERTICAL,
		SNAKE_HORIZONTAL
	};

	int neighbourhood[8];
	int goal_direction[4];

	int observePoint(SnakeObservation);

	bool operator==(const SnakeState& other) const
	{
		bool neighbour_eq = true;
		bool goal_direction_eq = true;
		for (int i = 0; i < 8; i++)
		{
			neighbour_eq &= neighbourhood[i] == other.neighbourhood[i];
		}

		for (int i = 0; i < 4; i++)
		{
			goal_direction_eq &= goal_direction[i] == other.goal_direction[i];
		}
		return neighbour_eq && goal_direction_eq;
	}
};

