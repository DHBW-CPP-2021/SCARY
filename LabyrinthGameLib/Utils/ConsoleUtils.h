#pragma once

#include <climits> // needed for INT_MAX (only for certain compiler maybe).
#include <string>
#include <vector>

namespace ConsoleUtils
{
    enum class Colors
    {
        FG_black = 30,
        BG_black = 40,
        FG_red = 31,
        BG_red = 41,
        FG_green = 32,
        BG_green = 42,
        FG_yellow = 33,
        BG_yellow = 43,
        FG_blue = 34,
        BG_blue = 44,
        FG_magenta = 35,
        BG_magenta = 45,
        FG_cyan = 36,
        BG_cyan = 46,
        FG_white = 37,
        BG_white = 47,
        X_reset = 0,  //(everything back to normal)
        X_bright = 1, //(often a brighter shade of the same colour)
        X_underline = 4,
        X_inverse = 7, //(swap foreground and background colours)
        X_brightOff = 21,
        X_underlineOff = 24,
        X_inverseOff = 27
    };

    int readInteger();
    long readLong();
    double readDouble();
    std::string readString();
    std::string readString(const std::string &message, int maxLength = INT_MAX);
    int safelyReadInteger(const std::string &message);
    int safelyReadInteger(const std::string &message, int min, int max);
    std::string colorString(const std::string &str, const std::vector<Colors> &opts);
    void clearConsole();
} // namespace ConsoleUtils
