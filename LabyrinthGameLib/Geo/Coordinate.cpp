#include "Coordinate.h"

namespace LabyrinthGame::Geo
{
	using namespace GameSettings;

	Coordinate::Coordinate(CoordType x_, CoordType y_) : _x(x_), _y(y_)
	{}

	CoordType Coordinate::getX() const
	{
		return _x;
	}

	CoordType Coordinate::getY() const
	{
		return _y;
	}

	bool Coordinate::isValid() const
	{
		// CoordType is an unsigned type, therefore we don't have to check for non-negativity
		return _x < GameSettings::WIDTH
			&& _y < GameSettings::HEIGHT;
	}

	Coordinate Coordinate::adjacentCoordinate(Direction const d) const {
		switch (d) {
		case Direction::up: return { _x,static_cast<CoordType>(_y - 1) };
		case Direction::down: return { _x,static_cast<CoordType>(_y + 1) };
		case Direction::left: return { static_cast<CoordType>(_x - 1),_y };
		case Direction::right: return { static_cast<CoordType>(_x + 1),_y };
		}
		throw std::runtime_error(&"LabyrinthGame::Direction.cpp: Apparently there are more then 4 directions, "
			"namely "[static_cast<int>(d)]);
	}

	std::ostream& operator<<(std::ostream& out, const Coordinate& c)
	{
		out << "(" << c.getX() << "," << c.getY() << ")";
		return out;
	}

	bool operator==(Coordinate const& left, Coordinate const& right)
	{
		return left.getX() == right.getX() && left.getY() == right.getY();
	}

	bool operator<(Coordinate const& left, Coordinate const& right)
	{
		return left.getX() < right.getX() || (left.getX() == right.getX() && left.getY() < right.getY());
	}
}
