#pragma once

#include "../GameBoard.h"
#include "../IO/DrawingConst.h"
#include "../Token/PlayerToken.h"
#include <array>

namespace LabyrinthGame
{
    struct PlacePartData
    {
        GameSettings::CoordType y;
        Geo::Direction direction; // hierüber kann herausgefunden werden ob in Row oder Col eingefügt wird.
        GameSettings::CoordType spare_piece_id;
    };
    class AbstractPlayer
    {
    public:
        using Coordinate = Geo::Coordinate;
        using DrawMatrix = std::array<std::array<char, IO::DrawingConst::inner_width>, IO::DrawingConst::inner_height>;

        AbstractPlayer(LabyrinthGame::GameBoard &board, Coordinate initialPos, DrawMatrix charRepresentation);
        virtual ~AbstractPlayer() = default;

        // methoden die die bot logik bzw die player abfrage implementieren
        virtual PlacePartData placePartDialog() = 0;
        virtual Coordinate movePlayerDialog() = 0;
        [[nodiscard]] Coordinate getCoordinate() const;

        void setCoordinates(const Coordinate &pos); //! Achtung kann gefährlich sein.
    protected:
        // ? Single Responsibility Principle: sollte das nicht in gameRules sein?!
        [[deprecated]] bool canMoveTo(
            const Coordinate &pos); // TODO Überall durch methode in GameRules ersetzen oder entfernen. Danach entfernen.

    private:
        PlayerToken m_token;
        const GameBoard &m_board;
    };
} // namespace LabyrinthGame