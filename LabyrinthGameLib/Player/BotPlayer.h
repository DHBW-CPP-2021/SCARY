#pragma once

#include "AbstractPlayer.h"

namespace LabyrinthGame
{
    class BotPlayer : public AbstractPlayer
    {
        using Coordinate = Geo::Coordinate;

    public:
        BotPlayer(LabyrinthGame::GameBoard &board, Coordinate initialPos, DrawMatrix charRepresentation);

        // methoden die die bot logik bzw die player abfrage implementieren
        [[nodiscard]] PlacePartData placePartDialog() const override;
        [[nodiscard]] Coordinate movePlayerDialog() const override;
    };
} // namespace LabyrinthGame