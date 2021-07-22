#include "GameRules.h"
#include "GameSettings.h"

LabyrinthGame::GameRules::GameRules(std::vector<std::weak_ptr<AbstractPlayer>> players, std::weak_ptr<GameBoard> board)
    : m_board(board), m_players(players)
{
}

bool LabyrinthGame::GameRules::checkMove(std::weak_ptr<AbstractPlayer> player, const Coordinate move)
{
    // Check if on piece is no other Player
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

    // check if Path is Connected
    return f_board->coordsAreConnected(move, f_player->getCoordinate());
}

bool LabyrinthGame::GameRules::checkPieceMove(const LabyrinthGame::PlacePartData &coordinatePartData)
{
    Coordinate coordinate = placePartDataToCoordinate(coordinatePartData);

    std::shared_ptr<GameBoard> f_board = m_board.lock();
    const Maze &maze = f_board->getMaze();

    return !maze.isFixed(coordinate)
}

bool LabyrinthGame::GameRules::checkWin(std::weak_ptr<AbstractPlayer> player)
{
    std::shared_ptr<AbstractPlayer> f_player = player.lock();

    // MAX_TREASURE == 3 in GameSettings
    return f_player->getTreasure() == LabyrinthGame::GameSettings::MAX_TREASURE && winPosition(f_player);
}

LabyrinthGame::GameRules::Coordinate LabyrinthGame::GameRules::placePartDataToCoordinate(
    const LabyrinthGame::PlacePartData &coordinatePartData)
{
    Coordinate coordinate(0, 0);
    switch (coordinatePartData.direction)
    {
    case LabyrinthGame::Geo::Direction::left:
        coordinate = Coordinate(7, coordinatePartData.ColOrRowIndex + 1);
        return coordinate;
    case LabyrinthGame::Geo::Direction::right:
        coordinate = Coordinate(0, coordinatePartData.ColOrRowIndex + 1);
        return coordinate;
    case LabyrinthGame::Geo::Direction::up:
        coordinate = Coordinate(coordinatePartData.ColOrRowIndex + 1, 7);
        return coordinate;
    case LabyrinthGame::Geo::Direction::down:
        coordinate = Coordinate(coordinatePartData.ColOrRowIndex + 1, 0);
        return coordinate;
    default:
        std::cerr << "Coordinate(0,0) in GameRules.cpp playePartDatatoCoordinate()\n";
        return coordinate;
    }
}

bool LabyrinthGame::GameRules::winPosition(std::weak_ptr<AbstractPlayer> player)
{
    std::shared_ptr<AbstractPlayer> f_player = player.lock();
    std::shared_ptr<GameBoard> f_board = m_board.lock();
    return f_board->coordIsConnectedToOutside(f_player->getCoordinate());
}