#pragma once
#include "Animal.h"
#include "FactoryAnimal.h"

class Goose : public Animal
{
public:
	Goose(const string& name, const Location& location);

	void step() override;
	void move() override;

protected:
	void setDirection() override;

private:
	Direction m_lastDirection = Direction::Stay;
	static bool m_registerit;

};