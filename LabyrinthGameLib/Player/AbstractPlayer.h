#pragma once

#include "../GameBoard.h"
#include "../IO/DrawingConst.h"
#include "../Token/PlayerToken.h"
#include <array>

namespace LabyrinthGame
{
    class AbstractPlayer
    {
    public:
        using Coordinate = Geo::Coordinate;
        using DrawMatrix = std::array<std::array<char, IO::DrawingConst::inner_width>, IO::DrawingConst::inner_height>;

        AbstractPlayer(LabyrinthGame::GameBoard &board, Coordinate initialPos, DrawMatrix charRepresentation);
        virtual ~AbstractPlayer() = default;

        // methoden die die bot logik bzw die player abfrage implementieren
        virtual void placePart() = 0;
        virtual void movePlayer() = 0;
        [[nodiscard]] Coordinate getCoordinate() const;

    protected:
        void move(const Coordinate &pos);

        // ? Single Responsibility Principle: sollte das nicht in gameRules sein?!
        bool canMoveTo(const Coordinate &pos);

    private:
        PlayerToken m_token;
        const GameBoard &m_board;
    };
} // namespace LabyrinthGame