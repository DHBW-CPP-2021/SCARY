#pragma once

#include "AbstractPlayer.h"

namespace LabyrinthGame
{
    class BotPlayer : public AbstractPlayer
    {
        using Coordinate = Geo::Coordinate;

    public:
        using AbstractPlayer::AbstractPlayer;

        // methoden die die bot logik bzw die player abfrage implementieren
        PlacePartData placePartDialog() override;
        Coordinate movePlayerDialog() override;
    };
} // namespace LabyrinthGame