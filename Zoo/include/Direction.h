#pragma once
#include "Utilities.h"
#include "Exception.h"
#include <typeinfo>
#include <typeindex>

enum class Direction {
    Stay,
    Up,
    Down,
    Right,
    Left,
    UpLeft,
    UpRight,
    DownLeft,
    DownRight
};

using Vector2 = pair<int, int>;
using DirectionMap = std::map<Direction, Vector2>;
Vector2 getDirection(Direction direction);



