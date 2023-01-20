#pragma once
#include "SnakeAgent.h"
#include "SnakeGame.h"
#include "Display.h"


class SnakeControl
{
public:
	~SnakeControl();
	void run();
	void step();

	void setGame(SnakeGame*);
	void setAgent(SnakeAgent*);

private:
	SnakeAgent* agent;
	SnakeGame* game;
	std::string display;
	double score;

	Display console_displayer;

	void displayState();
	void resetGame();
};

