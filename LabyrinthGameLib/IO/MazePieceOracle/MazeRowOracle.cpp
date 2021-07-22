#include "MazeRowOracle.h"
#include "../../Token/PlacedToken.h"

namespace LabyrinthGame
{
	namespace IO
	{
		using namespace Geo;

		GameSettings::CoordType MazeRowOracle::numPieces() const
		{
			return GameSettings::WIDTH;
		}

		MazePiece const& MazeRowOracle::getMazePiece(GameSettings::CoordType x) const
		{
			assert(x < GameSettings::WIDTH);
			return _board.getMaze().getPiece(coord(x));
		}

		MazeRowOracle::MazeRowOracle(GameBoard const& board_, GameSettings::CoordType y_)
			:
			_board(board_), _y(y_)
		{
			assert(y_ < GameSettings::HEIGHT);
		}

		bool MazeRowOracle::isTokenPlaced(GameSettings::CoordType x) const
		{
			assert(x < GameSettings::WIDTH);
			return _board.isTokenPlaced(coord(x));
		}

		const Token& MazeRowOracle::getPlacedToken(GameSettings::CoordType x) const
		{
			assert(isTokenPlaced(x));
			return _board.getToken(coord(x));
		}

		bool MazeRowOracle::isFixed(GameSettings::CoordType x) const
		{
			assert(x < GameSettings::WIDTH);
			return _board.getMaze().isFixed(coord(x));
		}

		Coordinate MazeRowOracle::coord(GameSettings::CoordType x) const
		{
			assert(x < GameSettings::WIDTH);
			return Coordinate(x, _y);
		}
	}
}

