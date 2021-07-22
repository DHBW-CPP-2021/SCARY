#include "GameRules.h"
#include "GameSettings.h"

LabyrinthGame::GameRules::GameRules(std::vector<std::weak_ptr<AbstractPlayer>> players, std::weak_ptr<GameBoard> board)
    : m_board(board), m_players(players)
{

}

bool LabyrinthGame::GameRules::checkMove(std::weak_ptr<AbstractPlayer> player,
                                         const LabyrinthGame::GameBoard::Coordinate move)
{

    return false;
}

bool LabyrinthGame::GameRules::checkPieceMove(const Coordinate &coordinate)
{
    // with Maze?  .isColumFixed() or isRawFixed()  in Board implemented ??
    return false;
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
    std::shared_ptr<GameBoard> board = m_board.lock();
    if (board->coordIsConnectedToOutside(f_player->getCoordinate()))
    {
        return true;
    }
    else
        return false;
}
