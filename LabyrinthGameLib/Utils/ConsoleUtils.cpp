#include "ConsoleUtils.h"

#include <cstddef>
#include <ctime>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int ConsoleUtils::readInteger()
{
    int result = -1;
    cin >> result;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return result;
}

long ConsoleUtils::readLong()
{
    long result = -1;
    cin >> result;
    return result;
}

double ConsoleUtils::readDouble()
{
    double result = -1;
    cin >> result;
    return result;
}

std::string ConsoleUtils::readString()
{
    string line;
    cin >> line;
    return line;
}

std::string ConsoleUtils::readString(const std::string &message, int maxLength)
{
    string line;
    while (line.empty() || line.length() > maxLength)
    {
        cout << message << endl;
        cin >> line;
    }
    return line;
}

int ConsoleUtils::safelyReadInteger(const string &message, int min, int max)
{
    int result = min - 1;
    while (result == min - 1)
    {
        cout << message << endl;
        result = readInteger();
        if (result < min || result > max)
        {
            cout << "Bitte einen Wert zwischen " << min << " und " << max << " eingeben!" << endl;
            result = min - 1;
        }
    }
    return result;
}

int ConsoleUtils::safelyReadInteger(const string &message)
{
    int result = -1;
    while (result == -1)
    {
        cout << message << endl;
        result = readInteger();
    }
    return result;
}

std::string ConsoleUtils::colorString(const std::string &str, const std::vector<Colors> &opts)
{
    std::string buff = "\033[";
    for (std::size_t i = 0; i < opts.size(); i++)
    {
        buff += std::to_string(static_cast<int>(opts[i]));
        if (i < opts.size() - 1)
        {
            buff += ';';
        }
    }
    buff += "m";
    return buff + str + "\033[0m";
}

void ConsoleUtils::clearConsole()
{
    std::cout << "\x1B[2J\x1B[H";
}