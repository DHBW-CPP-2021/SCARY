#include "SmartbotPlayer.h"

namespace LabyrinthGame
{
    using namespace Geo;
    SmartbotPlayer::SmartbotPlayer(LabyrinthGame::GameBoard &board, Coordinate initialPos, DrawMatrix charRepresentation)
        : AbstractPlayer(board, initialPos, charRepresentation)
    {
    }
    PlacePartData SmartbotPlayer::placePartDialog() const
    {
        return {0, Geo::Direction::left, 0};
    }
    Coordinate SmartbotPlayer::movePlayerDialog() const
    {
        return {0, 0};
    }
} // namespace LabyrinthGame