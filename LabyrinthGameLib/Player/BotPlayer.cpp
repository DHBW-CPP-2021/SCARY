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
        int SparePiece = (rand() % 3) + 1;

        int randomDirection = (rand() % 3);
        static_cast Geo::Direction(int);

        int row = (rand() % 7);

        return {SparePiece, Geo::Direction(randomDirection), row};
    }
    Coordinate BotPlayer::movePlayerDialog() const
    {
        int y = (rand() % 7);
        int x = (rand() % 7);
        return {y,x};
    }
} // namespace LabyrinthGame