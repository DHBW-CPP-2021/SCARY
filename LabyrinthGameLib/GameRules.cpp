#include "GameRules.h"
#include "GameSettings.h"

LabyrinthGame::GameRules::GameRules(std::vector<std::weak_ptr<AbstractPlayer>> players, std::weak_ptr<GameBoard> board)
{
    m_board = board;
    m_players = players;
}

bool LabyrinthGame::GameRules::checkWin(std::weak_ptr<AbstractPlayer> player)
{
    std::shared_ptr<AbstractPlayer> f_player = player.lock();
    //MAX_TREASURE == 3 in GameSettings
    if (f_player->getTreasuer() == LabyrinthGame::GameSettings::MAX_TREASURE && winPosition(f_player))
        return true;
    else
        return false;
}

bool LabyrinthGame::GameRules::winPosition(std::weak_ptr<AbstractPlayer> player)
{

    if (board.coordIsConnectedToOutside(player.getCoordinate()))
    {
        return true;
    }
    else
        return false;
}
