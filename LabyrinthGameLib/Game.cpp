#include "Game.h"
#include "IO/ConsoleUtils.h"
#include "IO/GameDrawer.h"
#include "Player/AbstractPlayer.h"

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
        std::cerr << "Game Board not available\n";
    else if (!createPlayers())
        std::cerr << "Players not available\n";
    else if (!createGameRules())
        std::cerr << "Rules not available\n";
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

        // Just for debug
        //
        /*Geo::Coordinate coords[4] = {Coordinate(0, 3), } */
        Geo::Coordinate coor(0, 0);
        DrawMatrix drawMatrix = {std::array<char, IO::DrawingConst::inner_width>{'P', 'l', 'a', 'y', 'e', 'r'},
                                 std::array<char, IO::DrawingConst::inner_width>{' ', ' ', ' ', ' ', ' ', ' '}};

        switch (i)
        {
        case 0:
            coor = Geo::Coordinate(0, 3);
            drawMatrix = DrawMatrix {std::array<char, IO::DrawingConst::inner_width>{'P', 'l', 'a', 'y', 'e', 'r'},
                                     std::array<char, IO::DrawingConst::inner_width>{' ', ' ', ' ', ' ', ' ', ' '}};
            break;
        case 1:
            coor = Geo::Coordinate(6, 3);
            drawMatrix = DrawMatrix{std::array<char, IO::DrawingConst::inner_width>{'P', 'l', 'a', 'y', 'e', 'r'},
                                    std::array<char, IO::DrawingConst::inner_width>{' ', ' ', ' ', ' ', ' ', ' '}};
            break;
        case 2:
            coor = Geo::Coordinate(3, 0);
            drawMatrix = DrawMatrix{std::array<char, IO::DrawingConst::inner_width>{'P', 'l', 'a', 'y', 'e', 'r'},
                                    std::array<char, IO::DrawingConst::inner_width>{' ', ' ', ' ', ' ', ' ', ' '}};
            break; 
        case 3:
            coor = Geo::Coordinate(3, 6);
            drawMatrix = DrawMatrix{std::array<char, IO::DrawingConst::inner_width>{'P', 'l', 'a', 'y', 'e', 'r'},
                                    std::array<char, IO::DrawingConst::inner_width>{' ', ' ', ' ', ' ', ' ', ' '}};
            break;
        default:
            break;
        }

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

bool LabyrinthGame::Game::createGameRules()
{
    std::vector<std::weak_ptr<AbstractPlayer>> temp;
    for (auto player : m_players)
    {
        temp.push_back(player);
    }
    m_rules = std::make_shared<GameRules>(temp, m_board);
    return m_rules != nullptr;
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
    bool checkInput = false;
    std::shared_ptr<AbstractPlayer> player = m_players[i];
    // Push the Piece/place the Part
    // [[nodiscard]] virtual PlacePartData placePartDialog() const = 0;

    LabyrinthGame::PlacePartData placedPart;
    //do while raus und prüfung in placePartDialog
    do
    {
        placedPart = player->placePartDialog();
        checkInput = m_rules->checkPieceMove(placedPart);

    } while (!checkInput);

    placePart(placedPart);

    Geo::Coordinate moveCoordinate(0, 0);
    do
    {
        moveCoordinate = player->movePlayerDialog();
        checkInput = m_rules->checkMove(player, moveCoordinate);

    } while (!checkInput);

    // player->setCoordinates(moveCoordinate); // get treasure in move or here and with parameter?
    player->setCoordinates(moveCoordinate); // get treasure in move or here and with parameter?

    if (m_board->isTokenPlaced(moveCoordinate))
    {
        player->addTreasure(); // remove Treasure from Board?
    }

    m_rules->checkWin(player);

    // shift the player
    if (i < m_players.size() - 1)
    {
        i++;
    }
    else
    {
        i = 0;
    }
    // clear Console
    LabyrinthGame::IO::ConsoleUtils::clearConsole();
    // print Board
    // IO::GameDrawer drawer(*m_board);
}

bool LabyrinthGame::Game::gameOver()
{
    bool win = 0;
    for (std::weak_ptr<AbstractPlayer> player : m_players)
    {
        win |= m_rules->checkWin(player);
    }
    return win;
}

bool LabyrinthGame::Game::placePart(LabyrinthGame::PlacePartData part)
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