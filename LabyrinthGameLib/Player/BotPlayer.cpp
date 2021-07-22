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
        std::uniform_real_distribution<int> dis(1, 3);
        int SparePiece = dis(generator);

        std::mt19937 generator(123);
        std::uniform_real_distribution<int> dis(0, 3);
        int randomDirection = dis(generator);

        static_cast Geo::Direction(int);


        std::mt19937 generator(123);
        std::uniform_real_distribution<int> dis(0, 7);
        int row = dis(generator);

        return {SparePiece, Geo::Direction(randomDirection), row};
    }
    Coordinate BotPlayer::movePlayerDialog() const
    {
        std::mt19937 generator(123);
        std::uniform_real_distribution<int> dis(0, 7);
        int y = dis(generator);

        std::mt19937 generator(123);
        std::uniform_real_distribution<int> dis(0, 7);
        int x = dis(generator)

        return {y,x};
    }
} // namespace LabyrinthGame