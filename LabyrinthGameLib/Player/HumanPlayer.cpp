#include "HumanPlayer.h"
#include "../GameSettings.h"
#include "../IO/ConsoleUtils.h"
#include "../IO/GameDrawer.h"
#include <stdexcept>
#include <stdio.h>
#include <string>
#include "../Game.h"

namespace LabyrinthGame
{
    using namespace Geo;
    HumanPlayer::HumanPlayer(LabyrinthGame::GameBoard &board, Coordinate initialPos, DrawMatrix charRepresentation, int id)
        : AbstractPlayer(board, initialPos, charRepresentation, id)
    {
    }
    char readChar(const std::string &dialog)
    {
        std::cout << dialog;
        std::string in;
        std::getline(std::cin, in);
        return in[0];
    }

    std::size_t getColOrRowIndex(const std::string &dialog, const std::array<const char, 15> &arr)
    {
        while (true)
        {
            char row = readChar(dialog);
            auto itt = std::find(std::begin(arr), std::end(arr), row);
            if (itt == std::end(arr))
            {
                std::cout << "this row/col does not exist\n";
                continue;
            }
            auto pos = std::distance(std::begin(arr), itt);
            if (pos % 2 == 0)
            {
                std::cout << "this row/col is fixed.\n";
                continue;
            }
            return pos;
        }
    }

    std::size_t getCoordinateXY(const std::string &dialog, const std::array<const char, 15> &arr)
    {
        while (true)
        {
            char row = readChar(dialog);
            auto itt = std::find(std::begin(arr), std::end(arr), row);
            if (itt == std::end(arr))
            {
                std::cout << "this row/col does not exist\n";
                continue;
            }
            return std::distance(std::begin(arr), itt);
        }
    }

    std::size_t getColIndex()
    {
        return getColOrRowIndex("Which Col?", IO::GameDrawer::xDigits);
    }
    std::size_t getRowIndex()
    {
        return getColOrRowIndex("Which Row?", IO::GameDrawer::yDigits);
    }

    PlacePartData HumanPlayer::placePartDialog() const
    {
        GameSettings::CoordType piece = IO::ConsoleUtils::safelyReadInteger(
            "which piece do you want to insert? (0-" + std::to_string(GameSettings::NUM_SPARE_PIECES - 1), 0,
            GameSettings::NUM_SPARE_PIECES - 1);
        int direction_numeric = IO::ConsoleUtils::safelyReadInteger(
            "where do you want to insert that piece?\n0 - top\n1 - right\n2 - bottom\n3 - left", 0, 3);

        using Dir = Geo::Direction;
        Dir direction;
        GameSettings::CoordType colOrRowIndex = 0;
        switch (direction_numeric)
        {
        case 0:
            direction = Dir::down;
            colOrRowIndex = getColIndex();
            break;
        case 1:
            direction = Dir::left;
            colOrRowIndex = getRowIndex();
            break;
        case 2:
            direction = Dir::up;
            colOrRowIndex = getColIndex();
            break;
        case 3:
            direction = Dir::right;
            colOrRowIndex = getRowIndex();
            break;
        default:
            throw std::runtime_error("this path should never be taken HumanPlayer.cpp");
        }
        return {colOrRowIndex, direction, piece};
    }
    Geo::Coordinate HumanPlayer::movePlayerDialog() const
    {
        std::cout <<  "Move the Player to the desired Coordinates\n";
        auto X = getCoordinateXY("X-Koordinate:", IO::GameDrawer::xDigits);
        auto Y = getCoordinateXY("Y-Koordinate:", IO::GameDrawer::yDigits);
        return {static_cast<GameSettings::CoordType>(X), static_cast<GameSettings::CoordType>(Y)};
    }
} // namespace LabyrinthGame