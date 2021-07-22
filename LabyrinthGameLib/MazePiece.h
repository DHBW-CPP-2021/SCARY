#ifndef HACKATHON_2021_MAZEPIECE_H
#define HACKATHON_2021_MAZEPIECE_H

#include "Geo/Direction.h"
#include "PathState.h"
#include <array>


namespace LabyrinthGame
{
    class MazePiece
    {
    public:
        MazePiece(PathState toLeft, PathState toRight, PathState up, PathState down);
        [[nodiscard]] PathState pathState(Geo::Direction d) const;
        [[nodiscard]] bool isClosed(Geo::Direction d) const;
        [[nodiscard]] bool isOpen(Geo::Direction d) const;
        [[maybe_unused]] void debugPrint() const;

    private:
        std::array<PathState, 4> const _path_states_per_direction;
    };

} // namespace LabyrinthGame

#endif // HACKATHON_2021_MAZEPIECE_H
