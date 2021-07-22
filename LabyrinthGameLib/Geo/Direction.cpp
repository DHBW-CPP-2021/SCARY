#include "Direction.h"
#include <stdexcept>


namespace LabyrinthGame::Geo
{
    bool isVertical(Direction direction)
    {
        return direction == Direction::up || direction == Direction::down;
    }
    bool isHorizontal(Direction direction)
    {
        return !isVertical(direction);
    }
    Direction oppositeDirection(Direction d)
    {
        switch (d)
        {
        case Direction::up:
            return Direction::down;
        case Direction::down:
            return Direction::up;
        case Direction::left:
            return Direction::right;
        case Direction::right:
            return Direction::left;
        }
        throw std::runtime_error(&"LabyrinthGame::Direction.cpp: Apparently there are more than 4 directions, "
                                  "namely "[static_cast<int>(d)]);
    }
} // namespace LabyrinthGame::Geo
