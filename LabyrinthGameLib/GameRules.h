#pragma once

#include "GameBoard.h"
#include "Geo/Coordinate.h"
#include "IO/MazePieceOracle/MazeRowOracle.h"
#include "Player/AbstractPlayer.h"
#include "Player/BotPlayer.h"
#include "Player/HumanPlayer.h"
#include "Player/SmartbotPlayer.h"
#include "Token/StupidToken.h"

namespace LabyrinthGame
{

    class GameRules
    {
        using Coordinate = Geo::Coordinate;

    public:
        GameRules(std::vector<std::weak_ptr<AbstractPlayer>> players, std::weak_ptr<GameBoard> board);
        //~GameRules();
        [[nodiscard]] bool checkMove(std::weak_ptr<AbstractPlayer> player, const Coordinate &move);
        [[nodiscard]] bool checkPieceMove(const LabyrinthGame::PlacePartData &coordinatePartData);
        [[nodiscard]] bool checkWin(std::weak_ptr<AbstractPlayer> player);
        [[nodiscard]] bool checkPieceForTreassure(const Geo::Coordinate &coordinate);

    private:
        [[nodiscard]] Coordinate placePartDataToCoordinate(const LabyrinthGame::PlacePartData &coordinatePartData);
        [[nodiscard]] bool winPosition(std::weak_ptr<AbstractPlayer> player);

        std::vector<std::weak_ptr<AbstractPlayer>> m_players;
        std::weak_ptr<GameBoard> m_board;
        std::vector<std::shared_ptr<Geo::Coordinate>> treasureCoords;
    };
} // namespace LabyrinthGame