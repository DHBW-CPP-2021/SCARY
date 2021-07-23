#include "Game.h"
#include "GameSettings.h"
#include "IO/ConsoleUtils.h"
#include "IO/GameDrawer.h"
#include "Player/AbstractPlayer.h"
#include <chrono>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

LabyrinthGame::Game::Game() = default;

void LabyrinthGame::Game::run()
{
    config();
    while (!gameOver())
    {
        round();
    }
}

void LabyrinthGame::Game::config()
{
    if (!createBoard())
    {
        std::cerr << "Game Board not available\n";
    }
    createPlayers();
    if (!createGameRules())
    {
        std::cerr << "Rules not available\n";
    }
    createTreasures();
}

bool LabyrinthGame::Game::createBoard()
{
    m_board = std::make_shared<GameBoard>();
    return m_board != nullptr;
}

void LabyrinthGame::Game::createPlayers()
{
    int anzahl = 2; // how many Players
    for (int i = 0; i < 2; i++)
    {
        // What kind of Player
        kindOfPlayer player = getPlayer(i + 1);
        Geo::Coordinate coor(0, 0);
        DrawMatrix drawMatrix = {std::array<std::string, IO::DrawingConst::inner_width>{"P", "l", "a", "y", "e", "r"},
                                 std::array<std::string, IO::DrawingConst::inner_width>{" ", " ", " ", " ", " ", " "}};

        coor = placePlayers(i);

        switch (player)
        {
        case kindOfPlayer::HUMANPLAYER:
            /*m_players[i] = std::make_shared<HumanPlayer>(*m_board, coor, drawMatrix);*/
            m_players.push_back(std::make_shared<HumanPlayer>(*m_board, coor, drawMatrix));
            break;
        case kindOfPlayer::DUMPBOT:
            m_players.push_back(std::make_shared<BotPlayer>(*m_board, coor, drawMatrix));
            break;
        case kindOfPlayer::SMARTBOT:
            m_players.push_back(std::make_shared<SmartbotPlayer>(*m_board, coor, drawMatrix));
            break;
        }
    }
}

void LabyrinthGame::Game::createTreasures()
{

    for (int i = 0; i < LabyrinthGame::GameSettings::MAX_TREASURES_GAME; i++)
    {
        int x = 0;
        int y = 0;
        Geo::Coordinate coordinate = createRandomCoordinate();

        // Ensure that no treassure is generated over another so there are always enough treasures
        while (!m_rules->checkPieceForTreassure(coordinate))
        {
            coordinate = createRandomCoordinate();
        }

        m_treasures.push_back(std::make_shared<TreasureToken>(*m_board, coordinate));
    }
}

bool LabyrinthGame::Game::createGameRules()
{
    std::vector<std::weak_ptr<AbstractPlayer>> temp;
    for (const auto &player : m_players)
    {
        temp.push_back(player);
    }
    m_rules = std::make_shared<GameRules>(temp, m_board);
    return m_rules != nullptr;
}

LabyrinthGame::Geo::Coordinate LabyrinthGame::Game::createRandomCoordinate()
{
    using CoordType = LabyrinthGame::GameSettings::CoordType;

    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_int_distribution<CoordType> CoordinationXArea(0, LabyrinthGame::GameSettings::WIDTH - 1);
    auto CoordinationX = CoordinationXArea(generator);
    CoordType x = CoordinationX % LabyrinthGame::GameSettings::WIDTH;

    std::uniform_int_distribution<int> CoordinationYArea(0, LabyrinthGame::GameSettings::HEIGHT - 1);
    auto CoordinationY = CoordinationYArea(generator);
    CoordType y = CoordinationY % LabyrinthGame::GameSettings::HEIGHT;

    return {x, y};
}

LabyrinthGame::Geo::Coordinate LabyrinthGame::Game::placePlayers(int i)
{
    // To Do different color for each Player !!!
    switch (i)
    {
    case 0:
        return Geo::Coordinate(0, LabyrinthGame::GameSettings::HEIGHT / 2);
    case 1:
        return Geo::Coordinate(LabyrinthGame::GameSettings::WIDTH - 1, LabyrinthGame::GameSettings::HEIGHT / 2);
    case 2:
        return Geo::Coordinate(LabyrinthGame::GameSettings::WIDTH / 2, 0);
    case 3:
        return Geo::Coordinate(LabyrinthGame::GameSettings::WIDTH / 2, LabyrinthGame::GameSettings::HEIGHT - 1);
    default:
        return Geo::Coordinate(0, 0);
    }
}

LabyrinthGame::kindOfPlayer LabyrinthGame::Game::getPlayer(int i)
{
    int playerIndex = IO::ConsoleUtils::safelyReadInteger(
        "Select the Player type for Player" + std::to_string(i) + "\n0-Human\n1-Bot\n2-SmartBot", 0, 2);
    return kindOfPlayer(playerIndex);
}

void LabyrinthGame::Game::round()
{
    for (const auto &player : m_players)
    {
        IO::GameDrawer drawer(*m_board);
        IO::ConsoleUtils::clearConsole();

        std::cout << "The Maze\n";
        drawer.drawMaze();
        std::cout << "\n\nAll the spare Pieces:\n";
        drawer.drawSparePieces();
        placePlayerSelectPiece(player);

        LabyrinthGame::IO::ConsoleUtils::clearConsole();

        std::cout << "The Maze\n";
        drawer.drawMaze();
        movePlayer(player);
        playerFindToken(player);

        LabyrinthGame::IO::ConsoleUtils::clearConsole();
    }
}

bool LabyrinthGame::Game::gameOver()
{
    bool win = false;
    for (const auto &player : m_players)
    {
        win |= m_rules->checkWin(player);
    }
    return win;
}

void LabyrinthGame::Game::placePart(const LabyrinthGame::PlacePartData &part)
{
    switch (part.direction)
    {
    case LabyrinthGame::Geo::Direction::down:
        m_board->insertSparePieceInColumn(part.ColOrRowIndex, part.direction, part.spare_piece_id);
        break;
    case LabyrinthGame::Geo::Direction::up:
        m_board->insertSparePieceInColumn(part.ColOrRowIndex, part.direction, part.spare_piece_id);
        break;
    case LabyrinthGame::Geo::Direction::left:
        m_board->insertSparePieceInRow(part.ColOrRowIndex, part.direction, part.spare_piece_id);
        break;
    case LabyrinthGame::Geo::Direction::right:
        m_board->insertSparePieceInRow(part.ColOrRowIndex, part.direction, part.spare_piece_id);
        break;
    }
}

void LabyrinthGame::Game::placePlayerSelectPiece(const std::shared_ptr<AbstractPlayer> &player)
{
    bool checkInput = false;
    LabyrinthGame::PlacePartData placedPart{};
    do
    {
        placedPart = player->placePartDialog();
        checkInput = m_rules->checkPieceMove(placedPart);

    } while (!checkInput);

    placePart(placedPart);
}

void LabyrinthGame::Game::movePlayer(const std::shared_ptr<AbstractPlayer> &player)
{
    Geo::Coordinate moveCoordinate(0, 0);
    bool checkInput = false;
    do
    {
        moveCoordinate = player->movePlayerDialog();
        checkInput = m_rules->checkMove(player, moveCoordinate);

    } while (!checkInput);

    player->setCoordinates(moveCoordinate); // get treasure in move or here and with parameter?
}

void LabyrinthGame::Game::playerFindToken(std::shared_ptr<AbstractPlayer> player)
{
    if (m_board->isTokenPlaced(player->getCoordinate()))
    {
        Geo::Coordinate playerCoord = player->getCoordinate();
        auto reachedTreasure = std::find_if(m_treasures.begin(), m_treasures.end(),
                                            [playerCoord](const std::shared_ptr<TreasureToken> &treasure) {
                                                return treasure->getCoordinate() == playerCoord;
                                            });
        if (reachedTreasure != m_treasures.end())
        {
            m_treasures.erase(reachedTreasure); // TODO memory leak ask paul???
        }

        player->addTreasure();
    }
}
