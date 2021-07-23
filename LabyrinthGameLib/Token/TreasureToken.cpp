#include "TreasureToken.h"
#include "../IO/ConsoleUtils.h"
#include "../Utils/Utils.h"
#include <cstddef>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

namespace LabyrinthGame
{
    using namespace Geo;

    void TreasureToken::notifyMovement(Direction d)
    {
        Coordinate const newCoord = getCoordinate().adjacentCoordinate(d);
        if (Utils::isValid(newCoord))
        {
            setCoordinate(newCoord);
        }
        // TODO this shouldn't look like the players logic, the treasure should always stay on the piece.
        else if (newCoord.getX() < 0) // piece moved out left
        {
            setCoordinate(Coordinate{GameSettings::WIDTH - 1, newCoord.getY()});
        }
        else if (newCoord.getX() > GameSettings::WIDTH - 1) // piece moved out right
        {
            setCoordinate(Coordinate{0, newCoord.getY()});
        }
        else if (newCoord.getY() > GameSettings::HEIGHT - 1) // piece moved out bottom
        {
            setCoordinate(Coordinate{newCoord.getX(), 0});
        }
        else if (newCoord.getY() < 0) // piece moved out top
        {
            setCoordinate(Coordinate{newCoord.getX(), GameSettings::HEIGHT - 1});
        }
        else
        {
            throw std::runtime_error("something went wrong... this shouldn't happen. check TreasureToken.cpp\n");
        }
    }

    std::pair<IO::Token::TokenArrayMatrix, std::size_t> getTreasureMatrix()
    {

        std::random_device rd;
        std::mt19937 generator{rd()};
        std::uniform_int_distribution<GameSettings::CoordType> SparePieceDist(0, 9);
        auto val = SparePieceDist(generator);
        using c = IO::ConsoleUtils::Colors;
        auto mat = std::array<std::array<std::string, 6>, 2>{
            std::array<std::string, 6>{IO::ConsoleUtils::colorString("T", {c::FG_yellow, c::BG_black}),
                                       IO::ConsoleUtils::colorString("r", {c::FG_yellow, c::BG_black}),
                                       IO::ConsoleUtils::colorString("e", {c::FG_yellow, c::BG_black}),
                                       IO::ConsoleUtils::colorString("a", {c::FG_yellow, c::BG_black}),
                                       IO::ConsoleUtils::colorString("s", {c::FG_yellow, c::BG_black}),
                                       IO::ConsoleUtils::colorString("u", {c::FG_yellow, c::BG_black})},
            std::array<std::string, 6>{IO::ConsoleUtils::colorString("r", {c::FG_yellow, c::BG_black}),
                                       IO::ConsoleUtils::colorString("e", {c::FG_yellow, c::BG_black}),
                                       IO::ConsoleUtils::colorString(std::to_string(val), {c::FG_yellow, c::BG_black}), " ",
                                       " ", " "}};
        return {mat, val};
    }
    std::size_t TreasureToken::getValue() const
    {
        return m_value;
    }

    TreasureToken::TreasureToken(GameBoard &board_, Coordinate initialPos)
        : m_randomNumandMat(getTreasureMatrix()), PlacedToken(board_, initialPos, m_randomNumandMat.first),
          m_value(m_randomNumandMat.second)
    {
    }

} // namespace LabyrinthGame