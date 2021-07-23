#include "AbstractPlayer.h"
#include "../../Graph/Algorithm/BreadthFirstSearch.h"
#include <stdexcept>

namespace LabyrinthGame
{

    AbstractPlayer::AbstractPlayer(LabyrinthGame::GameBoard &board, Coordinate initialPos, DrawMatrix charRepresentation)
        : m_token(board, initialPos, charRepresentation), m_board(board)
    {
        m_treasureIndex = 0;
    }

    void AbstractPlayer::addTreasure()
    {
        if (m_treasureIndex < 3)
        {
            m_treasureIndex++;
        }
    }
    void AbstractPlayer::setCoordinates(const Coordinate &pos)
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

    unsigned short AbstractPlayer::getTreasure()
    {
        return m_treasureIndex;
    }
    
    bool AbstractPlayer::canMoveTo(const Coordinate &pos)
    {
        return m_board.coordsAreConnected(pos, getCoordinate());
    }
} // namespace LabyrinthGame