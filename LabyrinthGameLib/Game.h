#pragma once
#include <vector>

#include "GameRules.h"
#include "GameBoard.h"
#include "IO/UserDecisions.h"
#include "GEO/Coordinate.h"



namespace LabyrinthGame
{

    enum class directions
    {
        a = 1,
        b = 2,
        c = 3,
        d = 4,
        e = 5,
        f = 6,
        g = 7
    };

    class Game
    {
    public:
        Game();
        void run();

    private:
        // ==== config methods ==========
        void config();
        bool createBoard();
        bool createPlayers();
        bool createGameRules();
        bool gameOver();

        // ==== round methods ===========
        void round();
        void playermove();

        // ==== members =================
        std::vector<std::shared_ptr<AbstractPlayer>> m_players;
        std::vector<std::shared_ptr<TreasureToken>> m_treasures;
        static std::shared_ptr<GameRules> m_rules;
        static std::shared_ptr<GameBoard> m_board;


    };
} // namespace LabyrinthGame