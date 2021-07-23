#include "gtest/gtest.h"
#include "../../../LabyrinthGameLib/GameSettings.h"
#include "../../../LabyrinthGameLib/Game.h"
#include "../../../LabyrinthGameLib/Player/AbstractPlayer.h"
#include "../../../LabyrinthGameLib/IO/GameDrawer.h"

using namespace LabyrinthGame;





class game : protected Game
{
public:
    using DrawMatrix = std::array<std::array<std::string, IO::DrawingConst::inner_width>, IO::DrawingConst::inner_height>;
    game(){}

    void config()
    {
        if (!createBoard())
        {
            std::cerr << "Game Board not available\n";
        }
        // How Many Players
        createPlayers();
        if (!createGameRules())
        {
            std::cerr << "Rules not available\n";
        }
        createTreasures();
    }

    void run()
    {
        config();
        while (!gameOver())
        {
            round();
        }
        IO::GameDrawer drawer(*m_board);
        std::cout << "The Maze\n";
        drawer.drawMaze();
    }

    void createPlayers()
    {
        std::vector<std::shared_ptr<AbstractPlayer>> players;
            Geo::Coordinate coor(0, 0);
            DrawMatrix drawMatrix = {std::array<std::string, IO::DrawingConst::inner_width>{"P", "l", "a", "y", "e", "r"},
                                     std::array<std::string, IO::DrawingConst::inner_width>{" ", " ", " ", " ", " ", " "}};

            coor = placePlayers(0);
            players.push_back(std::make_shared<BotPlayer>(*m_board, coor, drawMatrix, 1));
            coor = placePlayers(1);
            players.push_back(std::make_shared<SmartbotPlayer>(*m_board, coor, drawMatrix, 2));

            m_board->setPlayers(players);
    }

};

TEST(testConversion, all)
{
    for (int i = 0; i < 100; i++)
    {
        game _game = game();
        _game.config();
        _game.run();
    }
}