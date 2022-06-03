#pragma once
#include "Utilities.h"
#include "Location.h"
#include "Direction.h"


class Animal
{
public:
	Animal(const string& name, const Location& location, const string& kind); // c-tor
	virtual ~Animal() = default;

	void printDetails();
	const char getInitial() const;
	virtual void move() = 0;
	void stop();
	virtual void step() = 0;

	void turnHorizontally();
	void turnVertically();

	Location getLocation() const;
	Location getLastLocation() const;

	const string getKind() const;

protected:
	const string m_name;
	Location m_location;
	Direction m_direction = Direction::Stay;

	Location m_lastLocation;

	const string m_kind;

	bool m_canMove = true;

	virtual void setDirection() = 0;

private:

};
