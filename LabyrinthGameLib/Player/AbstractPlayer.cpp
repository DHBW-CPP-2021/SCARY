#include "AbstractPlayer.h"
#include "../../Graph/Algorithm/BreadthFirstSearch.h"
#include "../Token/TreasureToken.h"
#include <stdexcept>

namespace LabyrinthGame
{

    AbstractPlayer::AbstractPlayer(LabyrinthGame::GameBoard &board, Coordinate initialPos, DrawMatrix charRepresentation, int id)
        : m_token(board, initialPos, charRepresentation), m_board(board), m_treasureValue(0), m_id(id)
    {
    }

    void AbstractPlayer::addTreasure(const TreasureToken& treasure)
    {
        m_treasureValue += treasure.getValue();
    }
    
    void AbstractPlayer::setCoordinates(const Coordinate &pos)
    {
        m_token.setCoordinate(pos);
    }

    int AbstractPlayer::getID()
    {
        return m_id;
    }

    Geo::Coordinate AbstractPlayer::getCoordinate() const
    {
        return m_token.getCoordinate();
    }

    std::size_t AbstractPlayer::getTreasure()
    {
        return m_treasureValue;
    }

    const GameBoard &AbstractPlayer::getGameBoard() const
    {
        return m_board;
    }

} // namespace LabyrinthGame