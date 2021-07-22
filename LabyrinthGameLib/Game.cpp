#include "Game.h"

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
    if (m_board != nullptr)
        return true;
    else
        return false;
}

bool LabyrinthGame::Game::createPlayers()
{
    int anzahl = 2; // how many Players
    for (int i = 0; i < 2; i++)
    {
        // What kind of Player
        kindOfPlayer player = getPlayer(i + 1);
        
        switch (player)
        {
        case kindOfPlayer::HUMANPLAYER:
            m_players[i] = std::make_shared<HumanPlayer>();
            break;
        case kindOfPlayer::DUMPBOT:
            m_players[i] = std::make_shared<BotPlayer>();
            break;
        case kindOfPlayer::SMARTBOT:
            m_players[i] = std::make_shared<SmartbotPlayer>();
            break;
        }
    }
    return true;
}

bool LabyrinthGame::Game::createGameRules()
{
    m_rules = std::make_shared<GameRules>(m_board, m_players);
    if (m_rules != nullptr)
        return true;
    else
        return false;
}

LabyrinthGame::kindOfPlayer LabyrinthGame::Game::getPlayer(int i)
{
    int _player;

    do
    {
        std::cout << "Please select which kind the " << i << ". player should be:";
        std::cin >> _player;
    } while (_player >= 0 && _player < 3);

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
        static int i;
        bool checkInput = false;
        std::shared_ptr<AbstractPlayer> player = m_players[i];
        // Push the Piece/place the Part
        // [[nodiscard]] virtual PlacePartData placePartDialog() const = 0;

        LabyrinthGame::PlacePartData placedPart;
        do
        {
            placedPart = player->PlacePartDialog();
            checkInput = m_rules->checkPieceMove(placedPart);

        } while (!checkInput);

        player->placePart(placedPart);

        // Player Move
        Geo::Coordinate moveCoordinate(0, 0);
        do
        {
            moveCoordinate = player->movePlayerDialog();
            checkInput = m_rules->checkMove(player, moveCoordinate);

        } while (!checkInput);

        player->move(moveCoordinate); // get treasure in move or here and with parameter?

        if (m_board->isTokenPlaced(moveCoordinate))
            player->setTreasure();

        m_rules->checkWin(player);

        // shift the player
        if (i < m_players.size() - 1)
            i++;
        else
            i = 0;
    }

    bool LabyrinthGame::Game::gameOver()
    {
        bool win = 0;
        for (std::weak_ptr<AbstractPlayer> player : m_players)
            win |= m_rules->checkWin(player);
       return win;
    }
