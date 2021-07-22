#include "PlacedToken.h"
#include "../GameBoard.h"

namespace LabyrinthGame
{

	PlacedToken::PlacedToken(GameBoard& _board, Token::TokenArrayMatrix const& character_representation)
		:
		Token(character_representation)
	{
		GameBoardPlacedTokenMediator::registerToken(this, _board);
	}

	PlacedToken::PlacedToken(GameBoard& _board, char single_char_representation)
		:
		Token(single_char_representation)
	{
		GameBoardPlacedTokenMediator::registerToken(this, _board);
	}
}
