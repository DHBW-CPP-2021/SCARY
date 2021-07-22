//
// Created by danie on 17.07.2021.
//

#include <iostream>
#include "StupidToken.h"
#include "../Utils/Utils.h"

namespace LabyrinthGame
{
	using namespace Geo;

	Coordinate StupidToken::getCoordinate() const
	{
		return _pos;
	}

	void StupidToken::notifyMovement(Direction d)
	{
		Coordinate const newCoord = _pos.adjacentCoordinate(d);
		if (Utils::isValid(newCoord))
		{
			_pos = newCoord;
		}
		else
		{
			std::cout << "Oh no! What shall I do?\n";
		}
	}

	StupidToken::StupidToken(GameBoard& board_, Coordinate initialPos, char singleCharRepresentation)
		:
		PlacedToken(board_, singleCharRepresentation),
		_pos(initialPos)
	{}

	StupidToken::StupidToken(GameBoard& board_, Coordinate initialPos, TokenArrayMatrix charRepresentation)
		:
		PlacedToken(board_, charRepresentation),
		_pos(initialPos)
	{}

}