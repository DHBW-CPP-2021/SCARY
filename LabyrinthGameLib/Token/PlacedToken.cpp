#include "PlacedToken.h"
#include "../GameBoard.h"

namespace LabyrinthGame
{
    Geo::Coordinate PlacedToken::getCoordinate() const
    {
        return m_pos;
    }

    PlacedToken::PlacedToken(GameBoard &_board, Coordinate initialPos,
                             Token::TokenArrayMatrix const &character_representation)
        : Token(character_representation), m_pos(initialPos)
    {
        GameBoardPlacedTokenMediator::registerToken(this, _board);
    }

    PlacedToken::PlacedToken(GameBoard &_board, Coordinate initialPos, char single_char_representation)
        : Token(single_char_representation), m_pos(initialPos)
    {
        GameBoardPlacedTokenMediator::registerToken(this, _board);
    }

    void PlacedToken::setCoordinate(const Geo::Coordinate &pos)
    {
        m_pos = pos;
    }
} // namespace LabyrinthGame
