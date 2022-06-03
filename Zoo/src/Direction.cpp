#include "Direction.h"

namespace
{
	DirectionMap initializeMap()
	{
		DirectionMap map;
		map[Direction::Up] = { 0, -1 };
		map[Direction::Down] = { 0, 1 };
		map[Direction::Right] = { 1, 0 };
		map[Direction::Left] = { -1, 0 };
		map[Direction::UpLeft] = { -1, -1 };
		map[Direction::UpRight] = { 1, -1 };
		map[Direction::DownLeft] = { -1, 1 };
		map[Direction::DownRight] = { 1, 1 };
		map[Direction::Stay] = { 0, 0 };
		return map;
	}

	Vector2 lookup(Direction direction) {
		static DirectionMap dirMap = initializeMap(); // only once
		auto mapEntry = dirMap.find(direction);
		if (mapEntry == dirMap.end())
			return { 0, 0 };
		return mapEntry->second;
	}
} // end namespace
//-------------------------------------------------------
Vector2 getDirection(Direction direction)
{
	return lookup(direction);
}
