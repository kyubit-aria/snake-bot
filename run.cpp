#include "SnakeGame.h"
#include "GreedySnake.h"
#include "SnakeControl.h"

int main()
{
    SnakeGame* game = new SnakeGame(10, 10);
    GreedySnake* greedy_snake_agent = new GreedySnake(game->getSnakeState());
    SnakeControl snake_controller;

    snake_controller.setGame(game);
    snake_controller.setAgent(greedy_snake_agent);

    for (int i = 0; i < 5; i++)
    {
        snake_controller.run();
    }
    SnakeGame* new_game = new SnakeGame(20, 40);
    snake_controller.setGame(new_game);

    for (int i = 0; i < 25; i++)
    {
        snake_controller.run();
    }

}