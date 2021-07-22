#include "BotPlayer.h"
#include <random>

namespace LabyrinthGame
{
    using namespace Geo;
    BotPlayer::BotPlayer(LabyrinthGame::GameBoard &board, Coordinate initialPos, DrawMatrix charRepresentation)
        : AbstractPlayer(board, initialPos, charRepresentation)
    {
    }
    PlacePartData BotPlayer::placePartDialog() const
    {
        std::mt19937 generator(123);
        std::uniform_int_distribution<GameSettings::CoordType> SparePieceDist(1, 3);
        auto SparePiece = SparePieceDist(generator);

        std::uniform_int_distribution<int> randomDirectionDist(0, 3);
        int randomDirection = randomDirectionDist(generator);

        std::uniform_int_distribution<GameSettings::CoordType> rowDist(0, 7);
        auto row = rowDist(generator);

        return {SparePiece, Geo::Direction(randomDirection), row};
    }
    Coordinate BotPlayer::movePlayerDialog() const
    {
        std::mt19937 generator(123);
        std::uniform_int_distribution<GameSettings::CoordType> yDist(0, 7);
        auto y = yDist(generator);

        std::uniform_int_distribution<GameSettings::CoordType> xDist(0, 7);
        auto x = xDist(generator);

        return {y, x};
    }
} // namespace LabyrinthGame