#include "SmartbotPlayer.h"
#include "../GameBoard.h"
#include <cmath>
#include <random>
#include <tuple>


namespace LabyrinthGame
{
    using namespace Geo;
    SmartbotPlayer::SmartbotPlayer(LabyrinthGame::GameBoard &board, Coordinate initialPos, DrawMatrix charRepresentation)
        : AbstractPlayer(board, initialPos, charRepresentation)
    {
    }

    double getDistanceBetweenPointsIgnoringWalls(const Coordinate &point1, const Coordinate &point2)
    {
        int xDist = point1.getX() - point2.getX();
        int yDist = point1.getY() - point2.getY();
        return std::sqrt(std::pow(xDist, 2) + std::pow(yDist, 2));
    }

    // this gets the point that is still reachable from A and closest to B.
    std::tuple<Coordinate, double> SmartbotPlayer::getClosestPointReachableFromAtoB(const Coordinate &A,
                                                                                    const Coordinate &B) const
    {
        Coordinate ClosestReachableFromAtoB{0, 0};
        double distance = -1;
        const GameBoard &board = getGameBoard();

        for (GameSettings::CoordType x = 0; x < GameSettings::WIDTH; x++)
        {
            for (GameSettings::CoordType y = 0; y < GameSettings::HEIGHT; y++)
            {
                Coordinate tmp{x, y};
                if (board.coordsAreConnected(A, tmp))
                {
                    double tmpDist = getDistanceBetweenPointsIgnoringWalls(A, tmp);
                    if (tmpDist < distance || distance == -1)
                    {
                        distance = tmpDist;
                        ClosestReachableFromAtoB = tmp;
                    }
                }
            }
        }
        return {ClosestReachableFromAtoB, distance};
    }

    Coordinate SmartbotPlayer::getClosestReachablePointToTreasure() const
    {
        Coordinate closestToTreasure = getCoordinate();
        double distance = -1;
        for (const auto &treasure : getGameBoard().getTreasures())
        {
            auto [point, tmpDist] = getClosestPointReachableFromAtoB(getCoordinate(), treasure->getCoordinate());
            if (tmpDist < distance || distance == -1)
            {
                distance = tmpDist;
                closestToTreasure = point;
            }
        }
        return closestToTreasure;
    }

    PlacePartData SmartbotPlayer::placePartDialog() const
    {
        std::random_device rd;
        std::mt19937 generator{rd()};

        std::uniform_int_distribution<GameSettings::CoordType> SparePieceDist(0, GameSettings::NUM_SPARE_PIECES - 1);
        auto SparePiece = SparePieceDist(generator);

        std::uniform_int_distribution<int> randomDirectionDist(0, 3);
        int randomDirection = randomDirectionDist(generator);

        std::uniform_int_distribution<GameSettings::CoordType> rowDist(0,
                                                                       std::max(GameSettings::HEIGHT, GameSettings::WIDTH));
        auto row = rowDist(generator);

        return {row, Geo::Direction(randomDirection), SparePiece};
    }
    Coordinate SmartbotPlayer::movePlayerDialog() const
    {
        return getClosestReachablePointToTreasure();
    }
} // namespace LabyrinthGame