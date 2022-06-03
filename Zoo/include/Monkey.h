#pragma once
#include "Animal.h"
#include "FactoryAnimal.h"

class Monkey : public Animal
{
public:
	Monkey(const string& name, const Location& location);

	void step() override;
	void move() override;


protected:
	int m_counterRandom;
	void setDirection() override;

private:
	static bool m_registerit;

};