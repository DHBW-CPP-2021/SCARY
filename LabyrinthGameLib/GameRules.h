#pragma once
#include "Game.h"
#include "Geo/Coordinate.h"
#include "GameBoard.h"
#include "IO/MazePieceOracle/MazeRowOracle.h"
#include "Token/StupidToken.h"
#include "Player/AbstractPlayer.h"
#include "Player/BotPlayer.h"
#include "Player/SmartbotPlayer.h"
#include "Player/HumanPlayer.h"

namespace LabyrinthGame
{

    class GameRules
    {
        using Coordinate = Geo::Coordinate;
    public:
        GameRules(std::vector<std::weak_ptr<AbstractPlayer>> players, std::weak_ptr<GameBoard> board);

        bool checkMove(std::weak_ptr<AbstractPlayer> player, const Coordinate move);
        bool checkPieceMove(const Coordinate &coordinate);
        bool checkWin(std::weak_ptr<AbstractPlayer> player);

    private:
        bool winPosition(std::weak_ptr<AbstractPlayer> player);
        std::vector<std::weak_ptr<AbstractPlayer>> m_players;
        std::weak_ptr<GameBoard> m_board;
    };
} // namespace LabyrinthGame