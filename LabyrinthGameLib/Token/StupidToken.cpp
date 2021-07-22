//
// Created by danie on 17.07.2021.
//

#include "StupidToken.h"
#include "../Utils/Utils.h"
#include <iostream>

namespace LabyrinthGame
{
    using namespace Geo;

    void StupidToken::notifyMovement(Direction d)
    {
        Coordinate const newCoord = getCoordinate().adjacentCoordinate(d);
        if (Utils::isValid(newCoord))
        {
            setCoordinate(newCoord);
        }
        else
        {
            std::cout << "Oh no! What shall I do?\n";
        }
    }

    StupidToken::StupidToken(GameBoard &board_, Coordinate initialPos, char singleCharRepresentation)
        : PlacedToken(board_, initialPos, singleCharRepresentation)
    {
    }

    StupidToken::StupidToken(GameBoard &board_, Coordinate initialPos, TokenArrayMatrix charRepresentation)
        : PlacedToken(board_, initialPos, charRepresentation)
    {
    }

} // namespace LabyrinthGame