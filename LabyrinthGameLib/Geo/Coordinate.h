#ifndef HACKATHON_2021_COORDINATE_H
#define HACKATHON_2021_COORDINATE_H

#include "../GameSettings.h"
#include "Direction.h"
#include <ostream>


namespace LabyrinthGame::Geo
{

    class Coordinate
    {
        using CoordType = GameSettings::CoordType;

    public:
        Coordinate(CoordType x_, CoordType y_);

        [[nodiscard]] CoordType getX() const;

        [[nodiscard]] CoordType getY() const;
        [[nodiscard]] bool isValid() const;

        /**
         * Returns the adjacent coordinate towards a direction d.
         * @param d A direction
         * @return Adjacent coordinate towards direction d
         * @example
         *  - Upper adjacent coordinate of {3,4} is {3,3}
         *  - Lower adjacent coordinate of {3,4} is {3,5}
         *  - Left adjacent coordinate of {3,4} is {2,4}
         *  - Right adjacent coordinate of {3,4} is {4,4}
         */
        [[nodiscard]] Coordinate adjacentCoordinate(Direction d) const;

    private:
        CoordType _x;
        CoordType _y;
    };

    std::ostream &operator<<(std::ostream &out, Coordinate const &c);
    bool operator==(Coordinate const &left, Coordinate const &right);
    bool operator<(Coordinate const &left, Coordinate const &right);

} // namespace LabyrinthGame::Geo
#endif // HACKATHON_2021_COORDINATE_H
