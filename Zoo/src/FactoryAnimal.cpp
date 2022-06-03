#include "FactoryAnimal.h"

unique_ptr<Animal> FactoryAnimal::create(const string& name, const Location& location,const string& kind)
{
	auto it = FactoryAnimal::getMap().find(kind);
	if (it == FactoryAnimal::getMap().end())
		return nullptr;
	return it->second(name, location);
}
//---------------------------------------------------------
bool FactoryAnimal::registerit(const string& name, pFnc func)
{
	FactoryAnimal::getMap().emplace(name, func);
	return true;
}
//-------------------------------------------------