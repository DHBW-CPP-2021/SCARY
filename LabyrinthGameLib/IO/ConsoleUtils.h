#pragma once

#include <climits> // needed for INT_MAX (only for certain compiler maybe).
#include <string>


namespace LabyrinthGame
{
    namespace IO
    {
        namespace ConsoleUtils
        {
            [[maybe_unused]] int readInteger();

            [[maybe_unused]] long readLong();

            [[maybe_unused]] double readDouble();

            [[maybe_unused]] std::string readString();

            [[maybe_unused]] std::string readString(const std::string &msg, int maxLength = INT_MAX);

            [[maybe_unused]] int safelyReadInteger(const std::string &msg);

            [[maybe_unused]] int safelyReadInteger(const std::string &message, int min, int max);
        } // namespace ConsoleUtils
    }     // namespace IO
} // namespace LabyrinthGame
