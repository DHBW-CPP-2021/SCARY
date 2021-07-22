#include "SparePieceOracle.h"

namespace LabyrinthGame
{
	namespace IO
	{
		GameSettings::CoordType SparePieceOracle::numPieces() const
		{
			return GameSettings::NUM_SPARE_PIECES;
		}

		const MazePiece&
			SparePieceOracle::getMazePiece(GameSettings::CoordType id) const
		{
			assert(id < numPieces());
			return _maze.getSparePiece(id);
		}

		bool SparePieceOracle::isTokenPlaced(GameSettings::CoordType id) const
		{
			assert(id < numPieces());
			// Spare pieces never contain token...
			return false;
		}

		const Token& SparePieceOracle::getPlacedToken(GameSettings::CoordType) const
		{
			throw std::runtime_error("Invalid call");
		}

		SparePieceOracle::SparePieceOracle(const Maze& maze_) : _maze(maze_)
		{}

		bool SparePieceOracle::isFixed(GameSettings::CoordType) const
		{
			return false;
		}
	}
}