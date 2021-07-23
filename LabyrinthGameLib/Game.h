#pragma once
#include <vector>

#include "GameBoard.h"
#include "GameRules.h"
#include "Player/AbstractPlayer.h"
#include "Token/TreasureToken.h"

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
        bool createBoard(); // TODO remove error code as return value
        void createPlayers();
        void createTreasures();
        bool createGameRules(); // TODO remove error code as return value
        [[nodiscard]] static LabyrinthGame::Geo::Coordinate createRandomCoordinate(); // TODO make coordinate return type
        // TODO refactor this method, this does not place players but the name says it does.
        [[nodiscard]] LabyrinthGame::Geo::Coordinate placePlayers(int i);
        // TODO same as above. getPlayer does not get player even tho the name suggest it does.
        [[nodiscard]] LabyrinthGame::kindOfPlayer getPlayer(int i);

        // Round Methods
        void round();
        [[nodiscard]] bool gameOver();
        void placePart(const LabyrinthGame::PlacePartData &part);
        void placePlayerSelectPiece(const std::shared_ptr<AbstractPlayer> &player);
        void movePlayer(const std::shared_ptr<AbstractPlayer> &player);
        void playerFindToken(
            std::shared_ptr<AbstractPlayer> player); // TODO name is not what it does and function needs major refactoring!!!

        // Members
        std::shared_ptr<GameRules> m_rules;
        std::shared_ptr<GameBoard> m_board;
    };

} // namespace LabyrinthGame