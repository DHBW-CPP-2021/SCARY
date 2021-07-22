#include "PlayerToken.h"
#include "../Utils/Utils.h"
#include <iostream>

namespace LabyrinthGame
{
    using namespace Geo;

    void PlayerToken::notifyMovement(Direction d)
    {
        Coordinate const newCoord = getCoordinate().adjacentCoordinate(d);
        if (Utils::isValid(newCoord))
        {
            setCoordinate(newCoord);
        }
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
            std::cerr << "something went wrong... this shouldn't happen. check playerToken.cpp\n";
        }
    }

    PlayerToken::PlayerToken(GameBoard &board_, Coordinate initialPos, char singleCharRepresentation)
        : PlacedToken(board_, initialPos, singleCharRepresentation)
    {
    }

    PlayerToken::PlayerToken(GameBoard &board_, Coordinate initialPos, TokenArrayMatrix charRepresentation)
        : PlacedToken(board_, initialPos, charRepresentation)
    {
    }

} // namespace LabyrinthGame