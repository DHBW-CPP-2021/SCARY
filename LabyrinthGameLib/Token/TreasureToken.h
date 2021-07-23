#pragma once
#include "PlacedToken.h"

namespace LabyrinthGame
{
    class TreasureToken : public PlacedToken
    {
        using Coordinate = Geo::Coordinate;

    public:
        TreasureToken(GameBoard &board_, Coordinate initialPos, int &treasureScore);
        
        [[nodiscard]] int getScore() const;
    private:
        void notifyMovement(Geo::Direction d) override;

        const int m_treasureScore;
    };

} // namespace LabyrinthGame
