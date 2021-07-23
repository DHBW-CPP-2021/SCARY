#pragma once

#include "../IO/DrawingConst.h"
#include "../Token/PlayerToken.h"
#include <array>


namespace LabyrinthGame
{
    class GameBoard;
    struct PlacePartData
    {
        GameSettings::CoordType ColOrRowIndex;
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
        [[nodiscard]] virtual PlacePartData placePartDialog() const = 0;
        [[nodiscard]] virtual Coordinate movePlayerDialog() const = 0;
        [[nodiscard]] Coordinate getCoordinate() const;
        [[nodiscard]] unsigned short getTreasure();

        void addTreasure();
        void setCoordinates(const Coordinate &pos); //! Achtung kann gefährlich sein.

    private:
        PlayerToken m_token;
        const GameBoard &m_board;
        unsigned short m_treasureIndex;
    };
} // namespace LabyrinthGame