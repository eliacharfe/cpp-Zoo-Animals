#include "Monkey.h"

bool Monkey::m_registerit = FactoryAnimal::registerit("Monkey", [](const std::string& name, const Location& location) ->
	std::unique_ptr<Animal> {return std::make_unique<Monkey>(name, location); }
);

Monkey::Monkey(const string& name, const Location& location)
	: Animal::Animal(name, location, "Monkey"), m_counterRandom(0)
{
	setDirection();
}
//--------------------------------
void Monkey::step()
{
	if (!m_canMove)
		return;

	m_lastLocation = m_location;

	if (m_counterRandom >= Max::RandomMonkey)
		setDirection();

	int random = rand() % 2;

	switch (random)
	{
	case 0: {
		if (m_direction == Direction::Right) {
			if (m_location._x >= Max::Width - 1)
				turnHorizontally();
			m_location._x += getDirection(m_direction).first;
		}
		if (m_direction == Direction::Left) {
			if (m_location._x <= 0)
				turnHorizontally();
			m_location._x += getDirection(m_direction).first;
		}
		if (m_direction == Direction::Up) {
			if (m_location._y <= 0)
				turnVertically();
			m_location._y += getDirection(m_direction).second;
		}
		if (m_direction == Direction::Down) {
			if (m_location._y >= Max::Height - 1)
				turnVertically();
			m_location._y += getDirection(m_direction).second;
		}
		break;
	}
	case 1: {
		if (m_direction == Direction::Right) {
			if (m_location._x >= Max::Width - 1)
				turnHorizontally();
			m_location._x += getDirection(m_direction).first;
			if (m_location._x >= Max::Width - 1)
				turnHorizontally();
			m_location._x += getDirection(m_direction).first;
		}
		if (m_direction == Direction::Left) {
			if (m_location._x <= 0)
				turnHorizontally();
			m_location._x += getDirection(m_direction).first;
			if (m_location._x <= 0)
				turnHorizontally();
			m_location._x += getDirection(m_direction).first;
		}
		if (m_direction == Direction::Up) {
			if (m_location._y <= 0)
				turnVertically();
			m_location._y += getDirection(m_direction).second;
			if (m_location._y <= 0)
				turnVertically();
			m_location._y += getDirection(m_direction).second;
		}
		if (m_direction == Direction::Down) {
			if (m_location._y >= Max::Height - 1)
				turnVertically();
			m_location._y += getDirection(m_direction).second;
			if (m_location._y >= Max::Height - 1)
				turnVertically();
			m_location._y += getDirection(m_direction).second;
		}

		break;
	}
	default:
		break;
	}

	++m_counterRandom;
}
//-----------------
void Monkey::move()
{
	m_canMove = true;
}
//-----------------------------------
void Monkey::setDirection()
{
	int random = rand() % 4;
	switch (random)
	{
	case 0: m_direction = Direction::Up; break;
	case 1: m_direction = Direction::Down; break;
	case 2: m_direction = Direction::Left; break;
	case 3: m_direction = Direction::Up; break;
	default:
		break;
	}
	m_counterRandom = 0;
}
