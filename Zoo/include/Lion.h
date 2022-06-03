#pragma once
#include "FactoryAnimal.h"
#include "Animal.h"

class Lion : public Animal
{
public:
	Lion(const string& name, const Location& location);

	void step() override;
	void move() override;

protected:
	void setDirection() override;

private:
	static bool m_registerit;

};