#include "BotPlayer.h"

namespace LabyrinthGame
{
    using namespace Geo;
    BotPlayer::BotPlayer(LabyrinthGame::GameBoard &board, Coordinate initialPos, DrawMatrix charRepresentation)
        : AbstractPlayer(board, initialPos, charRepresentation)
    {
    }
    PlacePartData BotPlayer::placePartDialog() const
    {
        return {0, Geo::Direction::left, 0};
    }
    Coordinate BotPlayer::movePlayerDialog() const
    {
        return {0, 0};
    }
} // namespace LabyrinthGame