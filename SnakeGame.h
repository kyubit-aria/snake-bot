#pragma once

#include <string>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <time.h>
#include "SnakeState.h"

class SnakeGame
{
public:
	struct Position
	{
		int vertical;
		int horizontal;
		Position(int v, int h)
			: 
			vertical(v),
			horizontal(h) {}
	};

	struct SnakeData
	{
		Position head;
		Position tail;
		SnakeData(int v_head, int h_head ,int v_tail, int h_tail) 
			:
			head(v_head, h_head),
			tail(v_tail, h_tail) {}
	};

	SnakeGame(int, int);
	~SnakeGame();

	double moveStep(SnakeState::Movement);
	void reset();

	std::string displayContent();
	SnakeState getSnakeState();
	SnakeState::GameState getGameState();

private:
	const double DEATH_VALUE = -100.0;
	const double IDLE_VALUE = -0.5;
	const double FRUIT_VALUE = 50.0;
	const double WIN_VALUE = 1000.0;

	int field_height;
	int field_width;
	int field_size;
	int secretIndex;

	SnakeState snake_state;

	Position fruit_position;
	std::list<Position> snake_body;
	SnakeState::Movement snake_direction;
	SnakeState::GameState game_state;
	SnakeState::Elements* game_field;


	SnakeState::Movement getAction();
	SnakeState::Elements elementAt(Position);
	SnakeState::Elements* allocateFieldSpace(int,int);

	Position getHeadOffsetPosition(SnakeState::Movement);
	
	double updateSnakeBody(SnakeState::Movement);
	double step();

	bool fieldDimensionsValid();
	bool snakePosValid();
	bool inBounds(Position);
	bool isLegal(SnakeState::Movement);

	void initSnake(Position);
	void setMovement(SnakeState::Movement);
	void setValAtPosition(Position, SnakeState::Elements);
	void placeHead();
	void placeFruit(Position);
	void placeRandomFruit();
	void updateSnakeState();
	void emptyField();
	void clear();
};