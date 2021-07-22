#include <cstddef>
#include <cmath>
#include <algorithm>
#include "Token.h"
#include "../IO/DrawingConst.h"

namespace LabyrinthGame::IO
{

	Token::Token(Token::TokenArrayMatrix const& characterRepresentation)
		: _character_representation(characterRepresentation)
	{}

	Token::TokenArrayMatrix buildSingleCharRepresentation(char single_char_representation)
	{
		using Matrix = Token::TokenArrayMatrix;
		using Row = Token::TokenArrayRow;

		// Precompute indices
		auto const center_row_index = static_cast<Matrix::size_type>(std::floor(IO::DrawingConst::inner_height / 2.));
		auto const center_column_index = static_cast<Row::size_type>(std::floor(IO::DrawingConst::inner_width / 2.));

		// Create result matrix
		Matrix res(Token::getEmptyTokenArrayMatrix());
		// Add char at the center
		res[center_row_index][center_column_index] = single_char_representation;
		return res;
	}

	Token::Token(char single_char_representation)
		:
		_character_representation(buildSingleCharRepresentation(single_char_representation))
	{}


	const Token::TokenArrayMatrix& Token::getCharacterRepresentation() const
	{
		return _character_representation;
	}

	Token::TokenArrayMatrix Token::getEmptyTokenArrayMatrix()
	{
		Token::TokenArrayMatrix res {};
		std::for_each(res.begin(), res.end(), [](Token::TokenArrayRow& v) {std::fill(v.begin(), v.end(), ' '); });
		return res;
	}
}
