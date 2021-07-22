#include "ConsoleUtils.h"

#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

namespace LabyrinthGame
{
    namespace IO
    {
        [[maybe_unused]] int ConsoleUtils::readInteger()
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

        [[maybe_unused]] long ConsoleUtils::readLong()
        {
            long result = -1;
            cin >> result;
            return result;
        }

        [[maybe_unused]] double ConsoleUtils::readDouble()
        {
            double result = -1;
            cin >> result;
            return result;
        }

        [[maybe_unused]] std::string ConsoleUtils::readString()
        {
            string line = "";
            cin >> line;
            return line;
        }

        [[maybe_unused]] std::string ConsoleUtils::readString(const std::string &message, int maxLength)
        {
            string line = "";
            while (line == "" || line.length() > static_cast<std::basic_string<char>::size_type>(maxLength))
            {
                cout << message << endl;
                cin >> line;
            }
            return line;
        }

        [[maybe_unused]] int ConsoleUtils::safelyReadInteger(const string &message, int min, int max)
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

        [[maybe_unused]] int ConsoleUtils::safelyReadInteger(const string &message)
        {
            int result = -1;
            while (result == -1)
            {
                cout << message << endl;
                result = readInteger();
            }
            return result;
        }
    } // namespace IO
} // namespace LabyrinthGame
