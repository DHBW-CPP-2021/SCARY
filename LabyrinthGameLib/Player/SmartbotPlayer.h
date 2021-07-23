#pragma once

#include "AbstractPlayer.h"

namespace LabyrinthGame
{
    class SmartbotPlayer : public AbstractPlayer
    {
    public:
        SmartbotPlayer(LabyrinthGame::GameBoard &board, Coordinate initialPos, DrawMatrix charRepresentation);

        // methoden die die bot logik bzw die player abfrage implementieren
        [[nodiscard]] PlacePartData placePartDialog() const override;
        [[nodiscard]] Coordinate movePlayerDialog() const override;

    private:
        [[nodiscard]] std::tuple<Coordinate, double> getClosestPointReachableFromAtoB(const Coordinate &A,
                                                                                      const Coordinate &B) const;
        [[nodiscard]] Coordinate getClosestReachablePointToTreasure() const;
    };
} // namespace LabyrinthGame