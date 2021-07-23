#include "Game.h"
#include "GameSettings.h"
#include "IO/ConsoleUtils.h"
#include "IO/GameDrawer.h"
#include "Player/AbstractPlayer.h"
#include <chrono>
#include <random>

LabyrinthGame::Game::Game()
{
}

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
    else if (!createPlayers())
    {
        std::cerr << "Players not available\n";
    }
    else if (!createGameRules())
    {
        std::cerr << "Rules not available\n";
    }
    else if (!createTreasures())
    {
        std::cerr << "Treasures not available\n";
    }
}

bool LabyrinthGame::Game::createBoard()
{
    m_board = std::make_shared<GameBoard>();
    return m_board != nullptr;
}

bool LabyrinthGame::Game::createPlayers()
{
    int anzahl = 2; // how many Players
    for (int i = 0; i < 2; i++)
    {
        // What kind of Player
        kindOfPlayer player = getPlayer(i + 1);
        Geo::Coordinate coor(0, 0);
        DrawMatrix drawMatrix = {std::array<char, IO::DrawingConst::inner_width>{'P', 'l', 'a', 'y', 'e', 'r'},
                                 std::array<char, IO::DrawingConst::inner_width>{' ', ' ', ' ', ' ', ' ', ' '}};

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
    return true;
}

bool LabyrinthGame::Game::createTreasures()
{

    for (int i = 0; i < LabyrinthGame::GameSettings::MAX_TREASURES_GAME; i++)
    {
        int x = 0;
        int y = 0;
        std::tie(x, y) = createRandomCoordinate();
        Geo::Coordinate coordinate(x, y);

        // Ensure that no treassure is generated over another so there are always enough treasures
        while (!m_rules->checkPieceForTreassure(coordinate))
        {
            std::tie(x, y) = createRandomCoordinate();
            Geo::Coordinate coord(x, y);
            coordinate = coord;
        }

        m_treasures.push_back(std::make_shared<TreasureToken>(*m_board, coordinate));
    }
    return false;
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

std::tuple<int, int> LabyrinthGame::Game::createRandomCoordinate()
{
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);

    std::uniform_int_distribution<int> CoordinationXArea(0, LabyrinthGame::GameSettings::WIDTH - 1);
    auto CoordinationX = CoordinationXArea(generator);
    int x = CoordinationX % LabyrinthGame::GameSettings::WIDTH;

    std::uniform_int_distribution<int> CoordinationYArea(0, LabyrinthGame::GameSettings::HEIGHT - 1);
    auto CoordinationY = CoordinationYArea(generator);
    int y = CoordinationY % LabyrinthGame::GameSettings::HEIGHT;

    return std::make_tuple(x, y);
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
    int _player;

    do
    {
        std::cout << "Please select which kind the " << i << ". player should be:";
        std::cin >> _player;
    } while (_player > 3 || _player < 0);

    switch (_player)
    {
    case 0:
        return kindOfPlayer::HUMANPLAYER;
    case 1:
        return kindOfPlayer::DUMPBOT;
    case 2:
        return kindOfPlayer::SMARTBOT;
    }
}

void LabyrinthGame::Game::round()
{
    IO::GameDrawer drawer(*m_board);
    std::cout << "Let's draw the initial maze\n";
    drawer.drawMaze();

    std::cout << "\n\n\nLet's draw the spare pieces\n";
    drawer.drawSparePieces();
    static int i;
    std::shared_ptr<AbstractPlayer> player = m_players[i];

    placePiece(player);

    LabyrinthGame::IO::ConsoleUtils::clearConsole();
    drawer.drawMaze();

    movePlayer(player);

    deleteToken(player);

    bool win = m_rules->checkWin(player);

    // shift to the player
    if (i < m_players.size() - 1)
    {
        i++;
    }
    else
    {
        i = 0;
    }

    LabyrinthGame::IO::ConsoleUtils::clearConsole();
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

bool LabyrinthGame::Game::placePart(const LabyrinthGame::PlacePartData &part)
{
    switch (part.direction)
    {
    case LabyrinthGame::Geo::Direction::down:
        if (part.ColOrRowIndex % 2 == 1)
        {
            m_board->insertSparePieceInColumn(part.ColOrRowIndex, part.direction, part.spare_piece_id);
        }
        return true;
    case LabyrinthGame::Geo::Direction::up:
        if (part.ColOrRowIndex % 2 == 1)
        {
            m_board->insertSparePieceInColumn(part.ColOrRowIndex, part.direction, part.spare_piece_id);
        }
        return true;
    case LabyrinthGame::Geo::Direction::left:
        if (part.ColOrRowIndex % 2 == 1)
        {
            m_board->insertSparePieceInRow(part.ColOrRowIndex, part.direction, part.spare_piece_id);
        }
        return true;
    case LabyrinthGame::Geo::Direction::right:
        if (part.ColOrRowIndex % 2 == 1)
        {
            m_board->insertSparePieceInRow(part.ColOrRowIndex, part.direction, part.spare_piece_id);
        }
        return true;
    default:
        return false;
    }
}

bool LabyrinthGame::Game::placePiece(std::shared_ptr<AbstractPlayer> player)
{
    bool checkInput = false;
    LabyrinthGame::PlacePartData placedPart;
    do
    {
        placedPart = player->placePartDialog();
        checkInput = m_rules->checkPieceMove(placedPart);

    } while (!checkInput);

    return placePart(placedPart);
}

bool LabyrinthGame::Game::movePlayer(std::shared_ptr<AbstractPlayer> player)
{
    Geo::Coordinate moveCoordinate(0, 0);
    bool checkInput = false;
    do
    {
        moveCoordinate = player->movePlayerDialog();
        checkInput = m_rules->checkMove(player, moveCoordinate);

    } while (!checkInput);

    player->setCoordinates(moveCoordinate); // get treasure in move or here and with parameter?
    return true;
}

bool LabyrinthGame::Game::deleteToken(std::shared_ptr<AbstractPlayer> player)
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
            m_treasures.erase(reachedTreasure); // To DO memory leak ask paul???
        }

        player->addTreasure();
    }
    return true;
}
