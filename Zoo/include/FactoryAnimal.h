#pragma once
#include "Utilities.h"
#include "Animal.h"

class FactoryAnimal : public Animal
{
public:
	using pFnc = unique_ptr<Animal>(*)(const string& , const Location& );
	static unique_ptr<Animal> create(const string& name, const Location& location, const string& kind);
	static bool registerit(const string& name, pFnc);
	
private:
	static auto& getMap() {
		static std::map < string, pFnc > map;
		return map;
	}
	
};
