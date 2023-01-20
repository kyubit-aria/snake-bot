#include "SnakeState.h"

int SnakeState::observePoint(SnakeObservation observation)
{
	switch (observation)
	{
	case SnakeObservation::TOP_LEFT:
	case SnakeObservation::ABOVE:
	case SnakeObservation::TOP_RIGHT:
	case SnakeObservation::TO_LEFT:
	case SnakeObservation::TO_RIGHT:
	case SnakeObservation::BOTTOM_LEFT:
	case SnakeObservation::BELOW:
	case SnakeObservation::BOTTOM_RIGHT:
		return neighbourhood[observation];

	case SnakeObservation::FRUIT_VERTICAL:
	case SnakeObservation::FRUIT_HORIZONTAL:
	case SnakeObservation::SNAKE_VERTICAL:
	case SnakeObservation::SNAKE_HORIZONTAL:
		return goal_direction[observation-8];
	}
    return 0;
}
