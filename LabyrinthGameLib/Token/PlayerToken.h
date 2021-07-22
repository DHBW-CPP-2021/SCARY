#pragma once
#include "PlacedToken.h"

namespace LabyrinthGame
{
    class PlayerToken : public PlacedToken
    {
        using Coordinate = Geo::Coordinate;

    public:
        PlayerToken(GameBoard &board_, Coordinate initialPos, char singleCharRepresentation);
        PlayerToken(GameBoard &board_, Coordinate initialPos, TokenArrayMatrix charRepresentation);

    private:
        void notifyMovement(Geo::Direction d) override;
    };

} // namespace LabyrinthGame
