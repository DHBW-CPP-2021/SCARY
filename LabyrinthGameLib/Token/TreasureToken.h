#pragma once
#include "PlacedToken.h"

namespace LabyrinthGame
{
    class TreasureToken : public PlacedToken
    {
        using Coordinate = Geo::Coordinate;

    public:
        TreasureToken(GameBoard &board_, Coordinate initialPos);
        [[nodiscard]] std::size_t getValue() const;

    private:
        std::pair<IO::Token::TokenArrayMatrix, std::size_t> m_randomNumandMat;
        std::size_t m_value;
        void notifyMovement(Geo::Direction d) override;

        const int m_treasureScore;
    };

} // namespace LabyrinthGame
