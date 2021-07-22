#ifndef HACKATHON_2021_UTILS_H
#define HACKATHON_2021_UTILS_H

#include "../GameSettings.h"
#include "../Geo/Coordinate.h"
#include <cstddef>


namespace LabyrinthGame
{

    namespace Utils
    {
        /**
         * For the sake of efficiency we also store fixed-sized two dimensional arrays
         * in one-dimensional datastructures. This methods maps the 2D coordinates
         * bijectively to an 1D index
         * @param coordinate a 2D-coordinate
         * @return One-dimensional array index corresponding to coordinate
         */
        [[nodiscard]] GameSettings::CoordType compute1DFrom2D(Geo::Coordinate const &coordinate);

        /**
         * Computes the 2D coordinate from a given 1D index
         * @param coord
         * @return 2D-coordinate
         */
        [[nodiscard]] Geo::Coordinate compute2DFrom1D(unsigned short coord);

        /**
         * Check whether a coordinates displays a valid point in the game
         * @param coordinate
         * @return True iff 0 < x < GameConstants::WIDTH && 0 < y < GameConstants::Height
         */
        [[nodiscard]] bool isValid(Geo::Coordinate const &coordinate);
    } // namespace Utils

} // namespace LabyrinthGame
#endif // HACKATHON_2021_UTILS_H
