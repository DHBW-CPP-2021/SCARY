#include "HumanPlayer.h"

namespace LabyrinthGame
{
    using namespace Geo;
    
    PlacePartData HumanPlayer::placePartDialog()
    {
        return {0, Geo::Direction::left, 0};
    }
    Geo::Coordinate HumanPlayer::movePlayerDialog()
    {
        return {0, 0};
    }
} // namespace LabyrinthGame