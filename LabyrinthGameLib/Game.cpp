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
        int kindOfPlayer = 0;
        switch (kindOfPlayer)
        {
        case 0:
            m_players[i] = std::make_shared<HumanPlayer>();
            break;
        case 1:
            m_players[i] = std::make_shared<BotPlayer>();
            break;
        case 2:
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

void LabyrinthGame::Game::round()
{
    static int i;
    std::shared_ptr<AbstractPlayer> player = players[i]->lock();
    //Push the Piece
    //input a-g 1/6 or 1-6 a/g  
    m_rules->checkPieceMove();
    m_players[i].pieceMove();
    //PLayer Move
    while (coordinate == 0)
    {
        player->movePlayerDialog();
    }
    //input coordinates to walk
    //check if players has 3 treasure and sit on a field where is open to the outside then WIN
    m_rules->checkMove();

    m_rules->checkWin(m_players[i]);
    m_players[i]->move();//get treasure in move or here and with parameter?
    
    
    //shift the player
    if (i < m_players.size())
        i++;
    else
        i = 0;




}
