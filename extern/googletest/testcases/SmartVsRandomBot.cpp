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
    using Game::getWinner;
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
        /*IO::GameDrawer drawer(*m_board);
        std::cout << "The Maze\n";
        drawer.drawMaze();*/
    }

    void createPlayers()
    {
        std::vector<std::shared_ptr<AbstractPlayer>> players;
            Geo::Coordinate coor(0, 0);
            DrawMatrix drawMatrix = {std::array<std::string, IO::DrawingConst::inner_width>{"P", "l", "a", "y", "e", "r"},
                                     std::array<std::string, IO::DrawingConst::inner_width>{" ", " ", " ", std::to_string(1), " ", " "}};

            coor = placePlayers(0);
            players.push_back(std::make_shared<SmartbotPlayer>(*m_board, coor, drawMatrix, 1));
            
            
            coor = placePlayers(1);

            drawMatrix = {
                std::array<std::string, IO::DrawingConst::inner_width>{"P", "l", "a", "y", "e", "r"},
                std::array<std::string, IO::DrawingConst::inner_width>{" ", " ", " ", std::to_string(2), " ", " "}};

            players.push_back(std::make_shared<BotPlayer>(*m_board, coor, drawMatrix, 2));

            m_board->setPlayers(players);
    }

};

int gamer()
{
    int counter = 0;
    for (int i = 0; i < 10; i++)
    {
        game _game = game();
        _game.config();
        _game.run();
        if (_game.getWinner() == 1)
            counter ++;
    }
    return counter;
}

TEST(TestConversion, all)
{
    ASSERT_GE(gamer(), 8);
}

//int gamer()
//{
//    game _game = game();
//    _game.config();
//    _game.run();
//    if (_game.getWinner() == 1)
//        return true;
//    return false;
//}
//
//
//TEST(Test1, all)
//{
//    ASSERT_TRUE(gamer());
//}
//TEST(Test2, all)
//{
//    ASSERT_TRUE(gamer());
//}
//TEST(Test3, all)
//{
//    ASSERT_TRUE(gamer());
//}
//TEST(Test4, all)
//{
//    ASSERT_TRUE(gamer());
//}
//TEST(Test5, all)
//{
//    ASSERT_TRUE(gamer());
//}
//TEST(Test6, all)
//{
//    ASSERT_TRUE(gamer());
//}
//TEST(Test7, all)
//{
//    ASSERT_TRUE(gamer());
//}
//TEST(Test8, all)
//{
//    ASSERT_TRUE(gamer());
//}
//TEST(Test9, all)
//{
//    ASSERT_TRUE(gamer());
//}
//TEST(Test10, all)
//{
//    ASSERT_TRUE(gamer());
//}
