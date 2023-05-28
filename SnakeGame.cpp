#include "SnakeGame.h"

SnakeGame::SnakeGame(int height, int width)
	:
	game_state(SnakeState::INVALID),
	game_field(NULL),
	snake_body(),
	field_height(height),
	field_width(width),
	field_size(height*width),
	snake_direction(SnakeState::UP),
	secretIndex(0),
	fruit_position(0,0)
{
	for (auto element : snake_state.neighbourhood) element = SnakeState::Elements::EMPTY;
	for (auto element : snake_state.goal_direction) element = 0;
	allocateFieldSpace(field_height, field_width);
	srand(time(NULL));
}

SnakeGame::~SnakeGame()
{
	if (game_field != NULL) free(game_field);
	snake_body.clear();
}

double SnakeGame::moveStep(SnakeState::Movement action)
{
	double score;
	setMovement(action);
	score = step();
	updateSnakeState();
	return double(score);
}

void SnakeGame::reset()
{
	game_state = SnakeState::STOPPED;
	int vertical_secret = rand() % (field_height);
	int horizontal_secret = rand() % (field_width);
	initSnake(Position(vertical_secret, horizontal_secret));

	emptyField();
	placeHead();
	placeRandomFruit();
	updateSnakeState();
}

std::string SnakeGame::displayContent()
{
	std::string temp;
	temp.append(field_width + 2, '-');
	temp.push_back('\n');
	for (int v = field_height - 1; v >= 0; v--)
	{
		temp.push_back('|');
		for (int h = 0; h < field_width; h++)
		{
			switch (game_field[v * field_width + h])
			{
			case SnakeState::EMPTY:
			{
				temp.push_back(' ');
				break;
			}
			case SnakeState::SNAKE:
			{
				temp.push_back('#');
				break;
			}
			case SnakeState::FRUIT:
			{
				temp.push_back('@');
				break;
			}
			}
		}
		temp.push_back('|');
		temp.push_back('\n');
	}
	temp.append(field_width + 2, '-');
	temp.push_back('\n');
	return std::string(temp);
}

SnakeState SnakeGame::getSnakeState()
{
	return SnakeState(snake_state);
}

SnakeState::GameState SnakeGame::getGameState()
{
	return game_state;
}

SnakeState::Movement SnakeGame::getAction()
{
	return snake_direction;
}

SnakeState::Elements SnakeGame::elementAt(Position pos)
{
	if (inBounds(pos))
	{
		return game_field[pos.vertical * field_width + pos.horizontal];
	}
	else
	{
		return SnakeState::EMPTY;
	}
}

SnakeState::Elements* SnakeGame::allocateFieldSpace(int height, int width)
{
	if (!fieldDimensionsValid())
	{
		game_state = SnakeState::INVALID;
		return game_field;
	}

	if (game_state == SnakeState::RUNNING) game_state = SnakeState::STOPPED;
	game_field = (SnakeState::Elements*) malloc( (height * width) * sizeof(SnakeState::Elements));

	if (game_field == NULL)
	{
		game_state = SnakeState::INVALID;
	}
	else
	{
		emptyField();
		game_state = SnakeState::READY;
	}

	return game_field;
}

SnakeGame::Position SnakeGame::getHeadOffsetPosition(SnakeState::Movement direction)
{
	switch (direction)
	{
		case SnakeState::UP: {return Position(snake_body.back().vertical + 1, snake_body.back().horizontal); }
		case SnakeState::DOWN: {return Position(snake_body.back().vertical - 1, snake_body.back().horizontal); }
		case SnakeState::LEFT: {return Position(snake_body.back().vertical, snake_body.back().horizontal - 1); }
		case SnakeState::RIGHT: {return Position(snake_body.back().vertical, snake_body.back().horizontal + 1); }
	}
}

double SnakeGame::updateSnakeBody(SnakeState::Movement movement)
{
	Position new_head_pos = getHeadOffsetPosition(movement);
	SnakeState::Elements value = elementAt(new_head_pos);

	snake_body.push_back(new_head_pos);
	setValAtPosition(snake_body.back(), SnakeState::SNAKE);

	if (value != SnakeState::FRUIT)
	{
		setValAtPosition(snake_body.front(), SnakeState::EMPTY);
		snake_body.pop_front();
		return IDLE_VALUE;
	}
	else
	{
		placeRandomFruit();
		return FRUIT_VALUE;
	}
}

double SnakeGame::step()
{
	if (!isLegal(snake_direction))
	{
		game_state = SnakeState::DIED;
		if (snake_body.size() >= field_size - 1)
		{
			return WIN_VALUE;
		}
		else
		{
			return DEATH_VALUE;
		}
	}
	else
	{
		return updateSnakeBody(snake_direction);
	}
}

bool SnakeGame::fieldDimensionsValid()
{
	return field_height > 0 && field_width > 0;
}

bool SnakeGame::snakePosValid()
{
	return 
		(snake_body.back().vertical >= 0 && snake_body.back().horizontal >= 0) &&
		(snake_body.back().vertical < field_height && snake_body.front().horizontal < field_width) &&
		(snake_body.back().vertical == snake_body.front().vertical &&
			snake_body.back().horizontal == snake_body.front().horizontal);
}

bool SnakeGame::inBounds(Position pos)
{
	return 
		(pos.vertical < field_height&& pos.horizontal < field_width) &&
		(pos.vertical >= 0 && pos.horizontal >= 0);
}

bool SnakeGame::isLegal(SnakeState::Movement mov)
{
	Position new_head_pos = getHeadOffsetPosition(mov);
	return 		
		(new_head_pos.vertical >= 0 && new_head_pos.horizontal >= 0) &&
		(new_head_pos.vertical < field_height&& new_head_pos.horizontal < field_width) &&
		(elementAt(new_head_pos) != SnakeState::SNAKE);
}

void SnakeGame::initSnake(Position pos)
{
	snake_body.clear();
	snake_body.push_back(pos);
}

void SnakeGame::setMovement(SnakeState::Movement direction)
{
	snake_direction = direction;
}

void SnakeGame::setValAtPosition(Position position, SnakeState::Elements value)
{
	game_field[position.vertical * field_width + position.horizontal] = value;
}

void SnakeGame::placeHead()
{
	game_field[snake_body.back().vertical * field_width + snake_body.back().horizontal] = SnakeState::SNAKE;
	game_state = SnakeState::READY;
}

void SnakeGame::placeFruit(Position pos)
{
	setValAtPosition(pos, SnakeState::FRUIT);
	fruit_position = Position(pos);
}

void SnakeGame::placeRandomFruit()
{
	secretIndex = rand() % (field_size);
	if (snake_body.size() == field_size) return;
	while (game_field[secretIndex % (field_size)] == SnakeState::SNAKE)
	{
		secretIndex = rand() % (field_size);
	};
	Position temp_position(secretIndex / field_width, secretIndex % field_width);
	placeFruit(temp_position);
}

void SnakeGame::updateSnakeState()
{
	SnakeGame::Position head_pos = snake_body.back();
	int temp_vertical = head_pos.vertical - 1;
	int temp_horizontal = head_pos.horizontal - 1;

	int index = 0;

	SnakeGame::Position temp_pos(0, 0);

	for (int i = 0; i < sense_range; i++)
	{
		for (int k = 0; k < sense_range; k++)
		{
			if (i == 1 && k == 1) continue;

			temp_pos = Position(temp_vertical + i, temp_horizontal + k);
			if (inBounds(temp_pos))
			{
				snake_state.neighbourhood[index++] = elementAt(temp_pos);
			}
			else
			{
				snake_state.neighbourhood[index++] = SnakeState::WALL;
			}
		}
	}

	snake_state.goal_direction[0] = fruit_position.vertical;
	snake_state.goal_direction[1] = fruit_position.horizontal;
	snake_state.goal_direction[2] = head_pos.vertical;
	snake_state.goal_direction[3] = head_pos.horizontal;
}

void SnakeGame::emptyField()
{
	for (int v = 0; v < field_height; v++)
	{
		for (int h = 0; h < field_width; h++)
		{
			game_field[v * field_width + h] = SnakeState::EMPTY;
		}
	}
	game_state = SnakeState::INVALID;
}

