#pragma once
#include "PlacedToken.h"

namespace LabyrinthGame
{
    class TreasureToken : public PlacedToken
    {
        using Coordinate = Geo::Coordinate;

    public:
        TreasureToken(GameBoard &board_, Coordinate initialPos, std::size_t random);
        [[nodiscard]] std::size_t getValue() const;

    private:
        std::size_t m_value;
        void notifyMovement(Geo::Direction d) override;
    };

} // namespace LabyrinthGame
