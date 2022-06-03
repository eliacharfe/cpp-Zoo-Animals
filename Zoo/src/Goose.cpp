#include "Goose.h"

bool Goose::m_registerit = FactoryAnimal::registerit("Goose", [](const std::string& name, const Location& location) ->
	std::unique_ptr<Animal> {return std::make_unique<Goose>(name, location); }
);

Goose::Goose(const string& name, const Location& location)
	: Animal::Animal(name, location, "Goose")
{
	while (m_lastDirection == m_direction
		|| (m_lastDirection == Direction::DownLeft && m_direction == Direction::UpRight)
		|| (m_lastDirection == Direction::DownRight && m_direction == Direction::UpLeft)
		|| (m_lastDirection == Direction::UpLeft && m_direction == Direction::DownRight)
		|| (m_lastDirection == Direction::UpRight && m_direction == Direction::DownLeft))
	{
		setDirection();
	}
}
//---------------------------
void Goose::step()
{
	if (!m_canMove)
		return;

	m_lastLocation = m_location;

	switch (m_lastDirection)
	{
	case Direction::DownLeft: {
		if (m_direction == Direction::DownRight) {
			if (m_location._y >= Max::Height - 1) {
				m_lastDirection = Direction::UpLeft;
				m_direction = Direction::UpRight;
				break;
			}

			m_location._x += getDirection(Direction::DownRight).first;
			m_location._y += getDirection(Direction::DownRight).second;
			m_lastDirection = Direction::DownRight;
			m_direction = Direction::DownLeft;
		}
		else if (m_direction == Direction::UpLeft) {
			if (m_location._x <= 1 || m_location._y <= 1 ) {
				m_lastDirection = Direction::DownRight;
				m_direction = Direction::UpRight;
				break;
			}
			m_location._x += getDirection(Direction::UpLeft).first;
			m_location._y += getDirection(Direction::UpLeft).second;
			m_lastDirection = Direction::UpLeft;
			m_direction = Direction::DownLeft;
		}

		break;
	}
	case Direction::DownRight: {
		if (m_direction == Direction::DownLeft) {
			if (m_location._y >= Max::Height -1 || m_location._x >= Max::Width - 1) {
				m_lastDirection = Direction::UpRight;
				m_direction = Direction::UpLeft;
				break;
			}
			m_location._x += getDirection(Direction::DownLeft).first;
			m_location._y += getDirection(Direction::DownLeft).second;
			m_lastDirection = Direction::DownLeft;
			m_direction = Direction::DownRight;
		}
		else if (m_direction == Direction::UpRight) {
			if (m_location._x >= Max::Width -1 || m_location._y >= Max::Height) {
				m_lastDirection = Direction::DownLeft;
				m_direction = Direction::UpLeft;
				break;
			}
			m_location._x += getDirection(Direction::UpRight).first;
			m_location._y += getDirection(Direction::UpRight).second;
			m_lastDirection = Direction::UpRight;
			m_direction = Direction::DownRight;
		}

		break;
	}
	case Direction::UpLeft: {
		if (m_direction == Direction::UpRight) {
			if (m_location._y <= 1 || m_location._x <= 1 || m_location._x >= Max::Width - 1) {
				m_lastDirection = Direction::DownLeft;
				m_direction = Direction::DownRight;
				break;
			}
			m_location._x += getDirection(Direction::UpRight).first;
			m_location._y += getDirection(Direction::UpRight).second;
			m_lastDirection = Direction::UpRight;
			m_direction = Direction::UpLeft;
		}
		else if (m_direction == Direction::DownLeft) {
			if (m_location._x <= 1 || m_location._y >= Max::Height -1) {
				m_lastDirection = Direction::UpRight;
				m_direction = Direction::DownRight;
				break;
			}
			m_location._x += getDirection(Direction::DownLeft).first;
			m_location._y += getDirection(Direction::DownLeft).second;
			m_lastDirection = Direction::DownLeft;
			m_direction = Direction::UpLeft;
		}

		break;
	}
	case Direction::UpRight: {
		if (m_direction == Direction::UpLeft) {
			if (m_location._y <= 1 || m_location._x <= 1 || m_location._x >= Max::Width - 1) {
				m_lastDirection = Direction::DownRight;
				m_direction = Direction::DownLeft;
				break;
			}
			m_location._x += getDirection(Direction::UpLeft).first;
			m_location._y += getDirection(Direction::UpLeft).second;
			m_lastDirection = Direction::UpLeft;
			m_direction = Direction::UpRight;
		}
		else if (m_direction == Direction::DownRight) {
			if (m_location._x >= Max::Width - 1 || m_location._y >= Max::Height -1) {
				m_lastDirection = Direction::UpLeft;
				m_direction = Direction::DownLeft;
				break;
			}
			m_location._x += getDirection(Direction::DownRight).first;
			m_location._y += getDirection(Direction::DownRight).second;
			m_lastDirection = Direction::DownRight;
			m_direction = Direction::UpRight;
		}

		break;
	}
	default:
		break;
	}
}
//-------------
void Goose::move()
{
	m_canMove = true;

	while (m_lastDirection == m_direction
		|| (m_lastDirection == Direction::DownLeft && m_direction == Direction::UpRight)
		|| (m_lastDirection == Direction::DownRight && m_direction == Direction::UpLeft)
		|| (m_lastDirection == Direction::UpLeft && m_direction == Direction::DownRight)
		|| (m_lastDirection == Direction::UpRight && m_direction == Direction::DownLeft))
	{
		setDirection();
	}

}
//-----------------------------
void Goose::setDirection()
{
	switch (rand() % 4)
	{
	case 0: m_direction = Direction::UpLeft; break;
	case 1: m_direction = Direction::UpRight; break;
	case 2: m_direction = Direction::DownLeft; break;
	case 3: m_direction = Direction::DownRight; break;
	default:
		break;
	}

	switch (rand() % 4)
	{
	case 0: m_lastDirection = Direction::UpLeft; break;
	case 1: m_lastDirection = Direction::UpRight; break;
	case 2: m_lastDirection = Direction::DownLeft; break;
	case 3: m_lastDirection = Direction::DownRight; break;
	default:
		break;
	}
}
