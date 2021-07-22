#ifndef HACKATHON_2021_MAZEPIECEORACLE_H
#define HACKATHON_2021_MAZEPIECEORACLE_H
#include "../../GameSettings.h"
#include "../../MazePiece.h"
#include "../../IO/Token.h"

namespace LabyrinthGame
{
	namespace IO
	{
		/**
		 * Abstract class
		 * A MazePieceOracle is a class, that gives you an ordered number of maze piece references
		 * It can be used to summarize a specific subset of maze pieces like the pieces belonging to a row of the maze
		 * or like all spare pieces.
		 * Maybe it could be useful to implement an iterator class in future
		 */
		class MazePieceOracle
		{
		public:
			[[nodiscard]] virtual GameSettings::CoordType numPieces() const = 0;

			[[nodiscard]] virtual MazePiece const& getMazePiece(GameSettings::CoordType id) const = 0;

			[[nodiscard]] virtual bool isFixed(GameSettings::CoordType id) const = 0;

			[[nodiscard]] virtual bool isTokenPlaced(GameSettings::CoordType id) const = 0;

			[[nodiscard]] virtual Token const& getPlacedToken(GameSettings::CoordType id) const = 0;
		};
	}
}
#endif //HACKATHON_2021_MAZEPIECEORACLE_H
