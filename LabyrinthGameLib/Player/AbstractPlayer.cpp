#include "AbstractPlayer.h"
#include "../../Graph/Algorithm/BreadthFirstSearch.h"
#include <stdexcept>

namespace LabyrinthGame
{

    AbstractPlayer::AbstractPlayer(LabyrinthGame::GameBoard &board, Coordinate initialPos, DrawMatrix charRepresentation)
        : m_token(board, initialPos, charRepresentation), m_board(board)
    {
    }
    void AbstractPlayer::move(const Coordinate& pos)
    {
        if (!canMoveTo(pos))
        {
            throw std::runtime_error("cant move to pos, you should've checked before moving!");
        }
        m_token.setCoordinate(pos);
    }

    Geo::Coordinate AbstractPlayer::getCoordinate() const
    {
        return m_token.getCoordinate();
    }
    
    bool AbstractPlayer::canMoveTo(const Coordinate &pos)
    {
        return m_board.coordsAreConnected(pos, getCoordinate());
    }
} // namespace LabyrinthGame