#include "GameRules.h"
#include "GameSettings.h"
#include "Utils/Utils.h"

LabyrinthGame::GameRules::GameRules(std::vector<std::weak_ptr<AbstractPlayer>> players, std::weak_ptr<GameBoard> board)
    : m_board(board), m_players(players)
{
    treasureCoords.assign({std::make_shared<Geo::Coordinate>(0, 3), std::make_shared<Geo::Coordinate>(3, 0),
                           std::make_shared<Geo::Coordinate>(6, 3), std::make_shared<Geo::Coordinate>(3, 6)});
}

bool LabyrinthGame::GameRules::checkMove(std::weak_ptr<AbstractPlayer> _player, const Coordinate &move)
{
    if (!LabyrinthGame::Utils::isValid(move))
    {
        return false;
    }

    std::shared_ptr<AbstractPlayer> f1_player = _player.lock();
    // Check if on piece is no other Player
    for (const std::weak_ptr<AbstractPlayer> &player : m_players)
    {
        std::shared_ptr<AbstractPlayer> f_player = player.lock();
        // todo check for himself???
        if (move == f_player->getCoordinate() && f_player != f1_player)
        {
            return false;
        }
    }
    std::shared_ptr<GameBoard> f_board = m_board.lock();

    // check if Path is Connected
    return f_board->coordsAreConnected(move, f1_player->getCoordinate());
}

bool LabyrinthGame::GameRules::checkPieceMove(const LabyrinthGame::PlacePartData &coordinatePartData)
{
    // check piece ID
    if (coordinatePartData.spare_piece_id > GameSettings::NUM_SPARE_PIECES - 1)
    {
        return false;
    }

    // check the coordinate
    Coordinate coordinate = placePartDataToCoordinate(coordinatePartData);
    if (!coordinate.isValid())
    {
        return false;
    }

    std::shared_ptr<GameBoard> f_board = m_board.lock();
    const Maze &maze = f_board->getMaze();

    return !maze.isFixed(coordinate);
}

bool LabyrinthGame::GameRules::checkWin(std::weak_ptr<AbstractPlayer> player)
{
    std::shared_ptr<AbstractPlayer> f_player = player.lock();

    // MAX_TREASURE == 3 in GameSettings
    // Output in Messageboxes?
    if (f_player->getTreasure() >= LabyrinthGame::GameSettings::MAX_TREASURE+3)
    {
        std::cout << "You just got three treasures. Your mission now is leaving the maze. Hurry!" << std::endl;
    }

    if (f_player->getTreasure() >= LabyrinthGame::GameSettings::MAX_TREASURE+3 && winPosition(f_player))
    {
        std::cout << "YOU WON, Player " << f_player->getID() <<"!" << std::endl;
        return true;
    }

    return false;
}

bool LabyrinthGame::GameRules::checkPieceForTreassure(const Geo::Coordinate &coordinate)
{
    auto occupied =
        std::find_if(treasureCoords.begin(), treasureCoords.end(),
                     [coordinate](const std::shared_ptr<Geo::Coordinate> &coord) { return *coord == coordinate; });

    if (occupied == treasureCoords.end())
    {
        treasureCoords.push_back(std::make_shared<Geo::Coordinate>(coordinate.getX(), coordinate.getY()));
        return true;
    }
    return false;
}

LabyrinthGame::GameRules::Coordinate LabyrinthGame::GameRules::placePartDataToCoordinate(
    const LabyrinthGame::PlacePartData &coordinatePartData)
{
    Coordinate coordinate(0, 0);
    switch (coordinatePartData.direction)
    {
    case LabyrinthGame::Geo::Direction::left:
        coordinate = Coordinate(6, coordinatePartData.ColOrRowIndex);
        return coordinate;
    case LabyrinthGame::Geo::Direction::right:
        coordinate = Coordinate(0, coordinatePartData.ColOrRowIndex);
        return coordinate;
    case LabyrinthGame::Geo::Direction::up:
        coordinate = Coordinate(coordinatePartData.ColOrRowIndex, 6);
        return coordinate;
    case LabyrinthGame::Geo::Direction::down:
        coordinate = Coordinate(coordinatePartData.ColOrRowIndex, 0);
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