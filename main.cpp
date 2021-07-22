#include "LabyrinthGameLib/GameBoard.h"
#include "LabyrinthGameLib/IO/GameDrawer.h"
#include "LabyrinthGameLib/Token/PlayerToken.h"
#include "LabyrinthGameLib/Token/TreasureToken.h"
#include <iostream>

int main()
{
    using namespace LabyrinthGame;
    using namespace LabyrinthGame::Geo;
    // TODO: Have fun and good luck!

    GameBoard board;
    IO::GameDrawer drawer(board);

    std::cout << "Let's draw the initial maze\n";
    drawer.drawMaze();

    std::cout << "\n\n\nLet's draw the spare pieces\n";
    drawer.drawSparePieces();

    std::cout << "\n\n\nLet's place some token!\n";
    PlayerToken t1(board, Coordinate(1, 1), 'x');
    // But the second one with a slightly more advanced char representation
    IO::Token::TokenArrayMatrix matrix = IO::Token::getEmptyTokenArrayMatrix();
    matrix[0][0] = 'a';
    matrix[0][1] = 'b';
    matrix[0][2] = 'c';
    matrix[1][3] = 'x';
    matrix[1][4] = 'y';
    matrix[1][5] = 'z';
    PlayerToken t2(board, Coordinate(2, 4), matrix);
    TreasureToken t3(board, Coordinate(3, 4));
    drawer.drawMaze();

    std::cout << "\n\n\nLet's insert the first spare piece into the second row!\n";
    board.insertSparePieceInRow(1, Direction::right, 0);
    drawer.drawMaze();

    return 0;
}