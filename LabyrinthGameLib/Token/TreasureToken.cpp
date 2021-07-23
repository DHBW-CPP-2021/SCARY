#include "TreasureToken.h"
#include "../Utils/Utils.h"
#include <iostream>
#include <stdexcept>

namespace LabyrinthGame
{
    using namespace Geo;

    void TreasureToken::notifyMovement(Direction d)
    {
        Coordinate const newCoord = getCoordinate().adjacentCoordinate(d);
        if (Utils::isValid(newCoord))
        {
            setCoordinate(newCoord);
        }
        // TODO this shouldn't look like the players logic, the treasure should always stay on the piece.
        else if (newCoord.getX() < 0) // piece moved out left
        {
            setCoordinate(Coordinate{GameSettings::WIDTH - 1, newCoord.getY()});
        }
        else if (newCoord.getX() > GameSettings::WIDTH) // piece moved out right
        {
            setCoordinate(Coordinate{0, newCoord.getY()});
        }
        else if (newCoord.getY() > GameSettings::HEIGHT) // piece moved out bottom
        {
            setCoordinate(Coordinate{newCoord.getX(), 0});
        }
        else if (newCoord.getY() < 0) // piece moved out top
        {
            setCoordinate(Coordinate{newCoord.getX(), GameSettings::HEIGHT - 1});
        }
        else
        {
            throw std::runtime_error("something went wrong... this shouldn't happen. check TreasureToken.cpp\n");
        }
    }

    constexpr IO::Token::TokenArrayMatrix getTreasureMatrix()
    {
        return std::array<std::array<char, 6>, 2>{std::array<char, 6>{'T', 'r', 'e', 'a', 's', 'u'},
                                                  std::array<char, 6>{'r', 'e', ' ', ' ', ' ', ' '}};
    }
    TreasureToken::TreasureToken(GameBoard &board_, Coordinate initialPos)
        : PlacedToken(board_, initialPos, getTreasureMatrix())
    {
    }

} // namespace LabyrinthGame