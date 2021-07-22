#pragma once
#include "Game.h"
#include "Geo/Coordinate.h"
#include "GameBoard.h"
#include "IO/MazePieceOracle/MazeRowOracle.h"

namespace LabyrinthGame
{

    class GameRules
    {
    public:
        GameRules(std::vector<std::weak_ptr<AbstractPlayer>> players, std::weak_ptr<GameBoard> board);

        bool checkMove(std::weak_ptr<AbstractPlayer> player, const Coordinate move);
        bool checkPieceMove();
        bool checkWin(std::weak_ptr<AbstractPlayer> player);

    private:
        bool winPosition(std::weak_ptr<AbstractPlayer> player);
        std::vector<std::weak_ptr<AbstractPlayer>> m_players;
        std::weak_ptr<GameBoard> m_board;
    };
} // namespace LabyrinthGame