#include "AbstractPlayer.h"

namespace LabyrinthGame
{

    AbstractPlayer::AbstractPlayer(LabyrinthGame::GameBoard &board, Coordinate initialPos, DrawMatrix charRepresentation)
        : m_token(board, initialPos, charRepresentation)
    {
    }
} // namespace LabyrinthGame