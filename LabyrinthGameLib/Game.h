#pragma once
#include <vector>

#include "GameBoard.h"
#include "GameRules.h"
#include "Token/TreasureToken.h"
#include "Player/AbstractPlayer.h"

namespace LabyrinthGame
{
    enum class kindOfPlayer
    {
        HUMANPLAYER = 0,
        DUMPBOT = 1,
        SMARTBOT = 2
    };

    class Game
    {
        using DrawMatrix = std::array<std::array<char, IO::DrawingConst::inner_width>, IO::DrawingConst::inner_height>;
    public:
        Game();
        void run();

    private:
        // config Methods
        void config();
        [[nodiscard]] bool createBoard();
        [[nodiscard]] bool createPlayers();
        [[nodiscard]] bool createGameRules();
        [[nodiscard]] LabyrinthGame::kindOfPlayer getPlayer(int i);

        // Round Methods
        void round();
        [[nodiscard]] bool gameOver();
        [[nodiscard]] bool placePart(LabyrinthGame::PlacePartData part);

        // Members
        std::vector<std::shared_ptr<AbstractPlayer>> m_players;
        //std::vector<std::shared_ptr<TreasureToken>> m_treasures;  can help for remove treasures???
        static std::shared_ptr<GameRules> m_rules;
        static std::shared_ptr<GameBoard> m_board; // static???
    };

} // namespace LabyrinthGame