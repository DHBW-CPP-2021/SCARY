#include "BotPlayer.h"

namespace LabyrinthGame
{
    using namespace Geo;
    BotPlayer::BotPlayer(LabyrinthGame::GameBoard &board, Coordinate initialPos, DrawMatrix charRepresentation)
        : AbstractPlayer(board, initialPos, charRepresentation)
    {
    }
    PlacePartData BotPlayer::placePartDialog() const
    {
        int SparePiece = (rand() % 3) + 1;
        
        int randomDirection = (rand() % 3);

        int row = (rand() % 7);
        
        return  {SparePiece, }


    Coordinate BotPlayer::movePlayerDialog() const
    {
        int MoveWidth = (rand() % 7);
        int MoveHeight = (rand() % 7);
        return
        {MoveHeight,MoveWidth};
    }
} // namespace LabyrinthGame