#include "GameRules.h"
#include "GameSettings.h"

LabyrinthGame::GameRules::GameRules(std::vector<std::weak_ptr<AbstractPlayer>> players, std::weak_ptr<GameBoard> board)
    : m_board(board), m_players(players)
{
}

bool LabyrinthGame::GameRules::checkMove(std::weak_ptr<AbstractPlayer> player, const Coordinate move)
{
    //Check if on piece is no other Player
    for (std::weak_ptr<AbstractPlayer> player : m_players)
    {
        std::shared_ptr<AbstractPlayer> f_player = player.lock();
        if (move == f_player->getCoordinate())
        {
            return false;
        }
    }
    std::shared_ptr<AbstractPlayer> f_player = player.lock();
    std::shared_ptr<GameBoard> f_board = m_board.lock();

    //check if Path is Connected
    return f_board->coordsAreConnected(move, f_player->getCoordinate());
}

bool LabyrinthGame::GameRules::checkPieceMove(const Coordinate &coordinate)
{
    std::shared_ptr<GameBoard> f_board = m_board.lock();
    Maze maze = f_board->getMaze();
    if (maze.isFixed(coordinate))
        return false;
    else
        return true;
}

bool LabyrinthGame::GameRules::checkWin(std::weak_ptr<AbstractPlayer> player)
{
    std::shared_ptr<AbstractPlayer> f_player = player.lock();
    // MAX_TREASURE == 3 in GameSettings
    if (f_player->getTreasuer() == LabyrinthGame::GameSettings::MAX_TREASURE && winPosition(f_player))
        return true;
    else
        return false;
}

bool LabyrinthGame::GameRules::winPosition(std::weak_ptr<AbstractPlayer> player)
{
    std::shared_ptr<AbstractPlayer> f_player = player.lock();
    std::shared_ptr<GameBoard> f_board = m_board.lock();
    if (f_board->coordIsConnectedToOutside(f_player->getCoordinate()))
    {
        return true;
    }
    else
        return false;
}
