#include "Lion.h"

bool Lion::m_registerit = FactoryAnimal::registerit("Lion", [](const std::string& name, const Location& location) ->
	std::unique_ptr<Animal> {return std::make_unique<Lion>(name, location); }
);

Lion::Lion(const string& name, const Location& location)
	: Animal::Animal(name, location, "Lion")
{
	setDirection();
}
//------------------------------
void Lion::step()
{
	if (!m_canMove)
		return;

	m_lastLocation = m_location;

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
}
//----------------------
void Lion::move()
{
	m_canMove = true;
}
//--------------------------
void Lion::setDirection()
{
	switch (rand() % 2)
	{
	case 0: m_direction = Direction::Right; break;
	case 1: m_direction = Direction::Left; break;
	default:   break;
	}
}
//--------------------------
