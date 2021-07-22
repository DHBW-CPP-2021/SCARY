#include "SmartbotPlayer.h"

namespace LabyrinthGame
{
    using namespace Geo;

    PlacePartData SmartbotPlayer::placePartDialog()
    {
        return {0, Geo::Direction::left, 0};
    }
    Coordinate SmartbotPlayer::movePlayerDialog()
    {
        return {0, 0};
    }
} // namespace LabyrinthGame