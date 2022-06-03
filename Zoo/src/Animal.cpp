#include "Animal.h"
#include "FactoryAnimal.h"

Animal::Animal(const string& name, const Location& location, const string& kind)
	: m_name(name), m_location(location), m_canMove(true), m_kind(kind)
{}
//-------------------------------------------
void Animal::printDetails()
{
	cout << m_name << " - "  << m_kind << " " << m_location << endl;
}
//---------------------------
const char Animal::getInitial() const
{
	return m_name[0];
}
//---------------------
void Animal::stop()
{
	m_canMove = false;
}
//----------------------------
void Animal::turnHorizontally()
{
	if (m_direction == Direction::Left)
		m_direction = Direction::Right;
	else if (m_direction == Direction::Right)
		m_direction = Direction::Left;
}
//------------------------------
void Animal::turnVertically()
{
	if (m_direction == Direction::Down)
		m_direction = Direction::Up;
	else if (m_direction == Direction::Up)
		m_direction = Direction::Down;
}
//----------------------------
Location Animal::getLocation() const
{
	return m_location;
}
//------------------------------------
Location Animal::getLastLocation() const
{
	return m_lastLocation;
}
//---------------------------------
const string Animal::getKind() const
{
	return m_kind;
}
