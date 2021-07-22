#include <iostream>
#include "MazePiece.h"

namespace LabyrinthGame
{

	using namespace LabyrinthGame::Geo;

	MazePiece::MazePiece(PathState toLeft, PathState toRight,
		PathState up, PathState down)
		:
		_path_states_per_direction({ toLeft,toRight,up,down })
	{}

	PathState MazePiece::pathState(Direction d) const
	{
		return _path_states_per_direction[static_cast<short unsigned>(d)];
	}

	bool MazePiece::isClosed(Direction d) const
	{
		return pathState(d) == PathState::closed;
	}

	bool MazePiece::isOpen(Direction d) const
	{
		return !isClosed(d);
	}

	std::string toString(PathState p)
	{
		return p == PathState::open ? "open" : "closed";
	}

	void MazePiece::debugPrint() const
	{
		std::cout << "left = " << toString(pathState(Direction::left)) << std::endl;
		std::cout << "top = " << toString(pathState(Direction::up)) << std::endl;
		std::cout << "right = " << toString(pathState(Direction::right)) << std::endl;
		std::cout << "bottom = " << toString(pathState(Direction::down)) << std::endl;
	}

} // namespace LabyrinthGame

