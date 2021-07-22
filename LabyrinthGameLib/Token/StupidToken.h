//
// Created by danie on 17.07.2021.
//

#ifndef HACKATHON_2021_STUPIDTOKEN_H
#define HACKATHON_2021_STUPIDTOKEN_H

#include "PlacedToken.h"

namespace LabyrinthGame
{
    /**
     * Just an example to get started. You most likely don't want to use this class (without adaption)
     */
    class StupidToken : public PlacedToken
    {
        using Coordinate = Geo::Coordinate;

    public:
        StupidToken(GameBoard &board_, Coordinate initialPos, char singleCharRepresentation);
        StupidToken(GameBoard &board_, Coordinate initialPos, TokenArrayMatrix charRepresentation);

        [[nodiscard]] Coordinate getCoordinate() const override;

        void notifyMovement(Geo::Direction d) override;

    private:
        Coordinate _pos;
    };

} // namespace LabyrinthGame

#endif // HACKATHON_2021_STUPIDTOKEN_H
