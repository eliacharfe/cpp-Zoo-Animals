#pragma once
#include "Utilities.h"

typedef struct Location
{
	int _x;
	int _y;

	Location() :
		Location(rand() % Width, rand() % Height)
	{ }

	Location(int x, int y) : _x(x), _y(y)
	{ }

	~Location() { }

	Location operator()(int x, int y) {
		Location location;
	    location._x = x;
		location._y = y;
		return location;
	}

	Location& operator+(const Location& other) const;
	Location& operator+= (const Location& other);

} Location;

std::ostream& operator<<(std::ostream& os, const Location& location);
const bool operator==(const Location& loc1, const Location& loc2);
const bool operator!=(const Location& loc1, const Location& loc2);
