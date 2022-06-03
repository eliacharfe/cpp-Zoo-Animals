#include "Location.h"


std::ostream& operator<<(std::ostream& os, const Location& location)
{
    os << "(" << location._x << "," << location._y << ")";
    	return os;
}
//----------------------------------------
const bool operator==(const Location& loc1, const Location& loc2)
{
    return (loc1._x == loc2._x) && (loc1._y == loc2._y);
}
//------------------------------------------------
const bool operator!=(const Location& loc1, const Location& loc2)
{
    return !(loc1 == loc2);
}
//--------------------------------------------
Location& Location::operator+(const Location& other) const
{
    Location location;
    location._x = _x + other._x;
    location._y = _y + other._y;
    return location;
}
//-----------------------------------------
Location& Location::operator+=(const Location& other)
{
    return *this = *this + other;
}
