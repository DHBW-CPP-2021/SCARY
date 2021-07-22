#pragma once

#include "AbstractPlayer.h"

namespace LabyrinthGame
{
    class HumanPlayer : public AbstractPlayer
    {
    public:
        using AbstractPlayer::AbstractPlayer;

        PlacePartData placePartDialog() override;
        Coordinate movePlayerDialog() override;
    };
} // namespace LabyrinthGame