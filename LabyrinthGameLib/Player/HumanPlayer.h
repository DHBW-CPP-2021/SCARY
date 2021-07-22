#pragma once

#include "AbstractPlayer.h"

namespace LabyrinthGame
{
    class HumanPlayer : public AbstractPlayer
    {
    public:
        using AbstractPlayer::AbstractPlayer;

        // methoden die die bot logik bzw die player abfrage implementieren
        void placePart() override;
        void movePlayer() override;
    };
} // namespace LabyrinthGame