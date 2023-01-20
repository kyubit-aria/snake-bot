#include <iostream>
#include <string>
#include <windows.h>

#include "SnakeGame.h"
#include "GreedySnake.h"
#include "Display.h"

int main()
{
    Display disp;

    SnakeGame game = SnakeGame(30, 60);
    game.reset();

    GreedySnake greedySnakeMover(game.getSnakeState());
    SnakeState::Movement next_move;
    double score = 0;
    while (true) {
        while (game.getGameState() != SnakeState::GameState::DIED)
        {
            greedySnakeMover.updateState(game.getSnakeState());
            next_move = greedySnakeMover.decideAction();
            score += game.moveStep(next_move);
            std::cout << game.displayContent().c_str() << std::endl;
            std::cout << "Score: " << std::fixed << score << std::endl;
            Sleep(10);
            disp.clearScreen();
        }
        game.reset();
        greedySnakeMover.updateState(game.getSnakeState());
        score = 0;
    }

}