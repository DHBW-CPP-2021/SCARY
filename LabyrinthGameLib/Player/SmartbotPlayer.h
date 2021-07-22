#pragma once

#include "AbstractPlayer.h"

namespace LabyrinthGame
{
    class SmartbotPlayer : public AbstractPlayer
    {
    public:
        SmartbotPlayer(LabyrinthGame::GameBoard &board, Coordinate initialPos, DrawMatrix charRepresentation);

        // methoden die die bot logik bzw die player abfrage implementieren
        PlacePartData placePartDialog() const override;
        Coordinate movePlayerDialog() const override;
    };
} // namespace LabyrinthGame