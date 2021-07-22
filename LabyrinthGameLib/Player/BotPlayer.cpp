#include "BotPlayer.h"

namespace LabyrinthGame
{
    using namespace Geo;
    
    PlacePartData BotPlayer::placePartDialog()
    {
        return {0, Geo::Direction::left, 0};
    }
    Coordinate BotPlayer::movePlayerDialog()
    {
        return {0, 0};
    }
} // namespace LabyrinthGame