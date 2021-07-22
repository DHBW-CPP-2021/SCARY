#include "GameRules.h"

GameRules::GameRules(std::vector<std::weak_ptr<AbstractPlayer>> players, std::weak_ptr<GameBoard> board)
{
    m_board = board;
    m_players = players;
}

bool GameRules::checkWin(std::weak_ptr<AbstractPlayer> player)
{
    if (player.getTreasuer() == 3 && winPosition(player))
        return true;
    else
        return false;
}

bool GameRules::winPosition(std::weak_ptr<AbstractPlayer> player)
{
    Coordinate coordinatePlayer = player.getPosition();
    if (coordinatePlayer.x == 0 || coordinatePlayer.x == 7 || coordinatePlayer.y == 0 || coordinatePlayer.y == 7)
    return true;
}
