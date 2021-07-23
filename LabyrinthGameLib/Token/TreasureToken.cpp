#include "TreasureToken.h"
#include "TreasureToken.h"
#include "../Utils/Utils.h"
#include "../IO/ConsoleUtils.h"
#include <iostream>
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
        else if (newCoord.getX() > GameSettings::WIDTH-1) // piece moved out right
        {
            setCoordinate(Coordinate{0, newCoord.getY()});
        }
        else if (newCoord.getY() > GameSettings::HEIGHT-1) // piece moved out bottom
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

    IO::Token::TokenArrayMatrix getTreasureMatrix()
    {
        return std::array<std::array<std::string, 6>, 2>{
            std::array<std::string, 6>{IO::ConsoleUtils::colorString("T", {IO::ConsoleUtils::Colors::FG_yellow, IO::ConsoleUtils::Colors::BG_black}),
                                       IO::ConsoleUtils::colorString("r", {IO::ConsoleUtils::Colors::FG_yellow, IO::ConsoleUtils::Colors::BG_black}),
                                       IO::ConsoleUtils::colorString("e", {IO::ConsoleUtils::Colors::FG_yellow, IO::ConsoleUtils::Colors::BG_black}),
                                       IO::ConsoleUtils::colorString("a", {IO::ConsoleUtils::Colors::FG_yellow, IO::ConsoleUtils::Colors::BG_black}),
                                       IO::ConsoleUtils::colorString("s", {IO::ConsoleUtils::Colors::FG_yellow, IO::ConsoleUtils::Colors::BG_black}),
                                       IO::ConsoleUtils::colorString("u", {IO::ConsoleUtils::Colors::FG_yellow, IO::ConsoleUtils::Colors::BG_black})},
            std::array<std::string, 6>{IO::ConsoleUtils::colorString("r", {IO::ConsoleUtils::Colors::FG_yellow, IO::ConsoleUtils::Colors::BG_black}),
                                       IO::ConsoleUtils::colorString("e", {IO::ConsoleUtils::Colors::FG_yellow, IO::ConsoleUtils::Colors::BG_black}),
                                       " ", " ", " ", " "}};

    }
    TreasureToken::TreasureToken(GameBoard &board_, Coordinate initialPos, int &treasureScore)
        : PlacedToken(board_, initialPos, getTreasureMatrix()), m_treasureScore(treasureScore)
    {
    }

    int TreasureToken::getScore() const
    {
        return m_treasureScore;
    }

} // namespace LabyrinthGame