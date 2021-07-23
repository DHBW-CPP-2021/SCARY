#include "BotPlayer.h"
#include <random>

namespace LabyrinthGame
{
    using namespace Geo;
    BotPlayer::BotPlayer(LabyrinthGame::GameBoard &board, Coordinate initialPos, DrawMatrix charRepresentation, int id)
        : AbstractPlayer(board, initialPos, charRepresentation, id)
    {
    }
    PlacePartData BotPlayer::placePartDialog() const
    {
        std::random_device rd;
        std::mt19937 generator{rd()};

        std::uniform_int_distribution<GameSettings::CoordType> SparePieceDist(0, GameSettings::NUM_SPARE_PIECES-1);
        auto SparePiece = SparePieceDist(generator);

        std::uniform_int_distribution<int> randomDirectionDist(0, 3);
        int randomDirection = randomDirectionDist(generator);

        std::uniform_int_distribution<GameSettings::CoordType> rowDist(0,
                                                                       std::max(GameSettings::HEIGHT, GameSettings::WIDTH));
        auto row = rowDist(generator);

        return {row, Geo::Direction(randomDirection), SparePiece};
    }
    Coordinate BotPlayer::movePlayerDialog() const
    {

        std::random_device rd;
        std::mt19937 generator{rd()};

        std::uniform_int_distribution<GameSettings::CoordType> yDist(0, 7);
        auto y = yDist(generator);

        std::uniform_int_distribution<GameSettings::CoordType> xDist(0, 7);
        auto x = xDist(generator);

        return {y, x};
    }
} // namespace LabyrinthGame