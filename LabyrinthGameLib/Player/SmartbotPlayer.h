#pragma once

#include "AbstractPlayer.h"

namespace LabyrinthGame
{
    class SmartbotPlayer : public AbstractPlayer
    {
    public:
        using AbstractPlayer::AbstractPlayer;

        // methoden die die bot logik bzw die player abfrage implementieren
        PlacePartData placePartDialog() override;
        Coordinate movePlayerDialog() override;
    };
} // namespace LabyrinthGame