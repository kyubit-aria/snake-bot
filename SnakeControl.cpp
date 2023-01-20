#include "SnakeControl.h"

void SnakeControl::resetGame()
{
	if (game == NULL) return;
	game->reset();
}

SnakeControl::~SnakeControl()
{
	if (agent != NULL)delete agent;
	if (game != NULL)delete agent;
}

void SnakeControl::run()
{
	resetGame();
	agent->setState(game->getSnakeState());
	while (game->getGameState() != SnakeState::GameState::DIED)
	{
		step();
		std::cout << display.c_str() << std::endl;
		Sleep(10);
		console_displayer.clearScreen();
	}
	score = 0;
}

void SnakeControl::step()
{
	if (game == NULL || agent == NULL) return;

	SnakeState::Movement next_move;
	display.clear();
	agent->setState(game->getSnakeState());

	next_move = agent->decideAction();

	score += game->moveStep(next_move);
	display.append(game->displayContent());
	display.append("Score: ");
	display.append(std::to_string(score));
}

void SnakeControl::setGame(SnakeGame* new_game)
{
	if (this->game != new_game)
	{
		delete game;
		game = new_game;
	}
}

void SnakeControl::setAgent(SnakeAgent* new_agent)
{
	if (this->agent != new_agent)
	{
		delete agent;
		agent = new_agent;
	}	
}

void SnakeControl::displayState()
{
	std::cout << display.c_str() << std::endl;
}
