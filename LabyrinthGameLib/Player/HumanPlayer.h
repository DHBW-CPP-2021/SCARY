#pragma once

#include "AbstractPlayer.h"

namespace LabyrinthGame
{
    class HumanPlayer : public AbstractPlayer
    {
    public:
        HumanPlayer(LabyrinthGame::GameBoard &board, Coordinate initialPos, DrawMatrix charRepresentation);

        [[nodiscard]] PlacePartData placePartDialog() const override;
        [[nodiscard]] Coordinate movePlayerDialog() const override;
    };
} // namespace LabyrinthGame