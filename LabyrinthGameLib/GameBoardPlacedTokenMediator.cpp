#include "GameBoardPlacedTokenMediator.h"
#include "GameBoard.h"
#include "Token/PlacedToken.h"

namespace LabyrinthGame
{
    void LabyrinthGame::GameBoardPlacedTokenMediator::registerToken(PlacedToken *token, GameBoard &board)
    {
        board.registerToken(token);
    }

    void GameBoardPlacedTokenMediator::notifyMovement(PlacedToken &token, Geo::Direction d)
    {
        token.notifyMovement(d);
    }
} // namespace LabyrinthGame