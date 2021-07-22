#pragma once
#include <vector>

#include "GameBoard.h"
#include "GameRules.h"
#include "Token/TreasureToken.h"
#include "Player/AbstractPlayer.h"

namespace LabyrinthGame
{

    class Game
    {
    public:
        Game();
        void run();

    private:
        void config();
        bool createBoard();
        bool createPlayers();
        bool createGameRules();
        bool gameOver();

        void round();
        std::vector<std::shared_ptr<AbstractPlayer>> m_players;
        std::vector<std::shared_ptr<TreasureToken>> m_treasures;
        static std::shared_ptr<GameRules> m_rules;
        static std::shared_ptr<GameBoard> m_board; // static???
    };

} // namespace LabyrinthGame