#include "UserDecisions.h"

LabyrinthGame::Geo::Coordinate LabyrinthGame::IO::UserDecisions::movePlayer()
{
    std::cout << "Please enter the field you want to move to [for example 2c]" << std::endl;
    std::string input;

    std::cin >> input;

    return UserDecisions::StringToCoordinate(input);
}

LabyrinthGame::Geo::Coordinate LabyrinthGame::IO::UserDecisions::StringToCoordinate(std::string coord)
{
    unsigned int _x = atoi(&coord[0]) - 1;
    unsigned int _y = 0;
    switch (coord[1])
    {
    case 'A':
    case 'a':
        break;
    case 'B':
    case 'b':
        _y = 1;
        break;
    case 'C':
    case 'c':
        _y = 2;
        break;
    case 'D':
    case 'd':
        _y = 3;
        break;
    case 'E':
    case 'e':
        _y = 4;
        break;
    case 'F':
    case 'f':
        _y = 5;
        break;
    case 'G':
    case 'g':
        _y = 6;
        break;
    }

    /*std::shared_ptr<LabyrinthGame::Geo::Coordinate> _coord = std::make_shared<LabyrinthGame::Geo::Coordinate>(_x, _y);*/
    LabyrinthGame::Geo::Coordinate _coord(_x, _y);
    return _coord;
}
