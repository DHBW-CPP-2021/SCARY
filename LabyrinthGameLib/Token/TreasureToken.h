#pragma once
#include "PlacedToken.h"

namespace LabyrinthGame
{
    class TreasureToken : public PlacedToken
    {
        using Coordinate = Geo::Coordinate;

    public:
        TreasureToken(GameBoard &board_, Coordinate initialPos);

    private:
        void notifyMovement(Geo::Direction d) override;
    };

} // namespace LabyrinthGame
