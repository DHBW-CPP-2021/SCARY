#pragma once

#include <string.h>
#include <iostream>

#include "../Geo/Coordinate.h"


namespace LabyrinthGame
{
    namespace IO
    {
        class UserDecisions
        {
        public:
            static LabyrinthGame::Geo::Coordinate movePlayer();

        private:
            static LabyrinthGame::Geo::Coordinate StringToCoordinate(std::string coord);
        };

    } // namespace IO
} // namespace LabyrinthGame