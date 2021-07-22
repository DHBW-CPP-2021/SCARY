#include "Utils.h"
#include "../GameSettings.h"
#include <cassert>


namespace LabyrinthGame
{

    using namespace Geo;

    GameSettings::CoordType Utils::compute1DFrom2D(const Coordinate &coordinate)
    {
        assert(coordinate.getY() * GameSettings::WIDTH + coordinate.getX() < GameSettings::NUM_COORDINATES);
        return coordinate.getY() * GameSettings::WIDTH + coordinate.getX();
    }

    Coordinate Utils::compute2DFrom1D(GameSettings::CoordType coord)
    {
        return Coordinate(coord % GameSettings::WIDTH, coord / GameSettings::WIDTH);
    }

    bool Utils::isValid(Coordinate const &coordinate)
    {
        return (coordinate.getX() < GameSettings::WIDTH && coordinate.getY() < GameSettings::HEIGHT);
    }
} // namespace LabyrinthGame
