cmake_minimum_required(VERSION 3.15)
project(Hackathon_2021)

set(CMAKE_CXX_STANDARD 17)

# include compiler warnings for unified compiler warnings along all devs
include(cmake/CompilerWarnings.cmake)

add_subdirectory(extern/googletest)

add_library(GraphLib
        STATIC
        Graph/Edge.cpp
        Graph/Edge.h
        Graph/Vertex.cpp
        Graph/Vertex.h
        Graph/Graph.cpp
        Graph/Graph.h
        Graph/Graph-commons.h
        Graph/PointerIteratorWrapper.h
        Graph/SimpleRange.h
        Graph/GraphMaps.h
        Graph/Algorithm/BreadthFirstSearch.cpp
        Graph/Algorithm/BreadthFirstSearch.h
        Graph/VertexVector.h)

set_project_warnings(GraphLib)

add_library(LoggerLib
        STATIC
        Logger/Logger.h
        Logger/LogPolicyInterface.h
        Logger/FileLogPolicy.cpp
        Logger/FileLogPolicy.h
        Logger/CoutLogPolicy.cpp
        Logger/CoutLogPolicy.h
        Logger/LogLevel.cpp
        Logger/LogLevel.h
        Logger/Log.h)

set_project_warnings(LoggerLib)
        
add_library(LabyrinthGameLib
        STATIC
        LabyrinthGameLib/IO/ConsoleUtils.cpp
        LabyrinthGameLib/IO/ConsoleUtils.h
        LabyrinthGameLib/MazePiece.cpp
        LabyrinthGameLib/MazePiece.h
        LabyrinthGameLib/Geo/Direction.h
        LabyrinthGameLib/Maze.cpp
        LabyrinthGameLib/Maze.h
        LabyrinthGameLib/IO/GameDrawer.cpp
        LabyrinthGameLib/IO/GameDrawer.h
        LabyrinthGameLib/GameSettings.h
        LabyrinthGameLib/GameBoard.cpp
        LabyrinthGameLib/GameBoard.h
        LabyrinthGameLib/Utils/Utils.cpp
        LabyrinthGameLib/Utils/Utils.h
        LabyrinthGameLib/Geo/Direction.cpp
        LabyrinthGameLib/IO/Token.cpp
        LabyrinthGameLib/IO/Token.h
        LabyrinthGameLib/IO/DrawingConst.h
        LabyrinthGameLib/Geo/Coordinate.cpp
        LabyrinthGameLib/Geo/Coordinate.h
        LabyrinthGameLib/IO/MazePieceOracle/MazePieceOracle.h
        LabyrinthGameLib/IO/MazePieceOracle/MazeRowOracle.cpp
        LabyrinthGameLib/IO/MazePieceOracle/MazeRowOracle.h
        LabyrinthGameLib/IO/MazePieceOracle/SparePieceOracle.cpp
        LabyrinthGameLib/IO/MazePieceOracle/SparePieceOracle.h
        LabyrinthGameLib/IO/UserDecisions.cpp
        LabyrinthGameLib/IO/UserDecisions.h
        LabyrinthGameLib/Token/PlacedToken.cpp 
        LabyrinthGameLib/Token/PlacedToken.h 
        LabyrinthGameLib/Token/StupidToken.cpp 
        LabyrinthGameLib/Token/StupidToken.h 
        LabyrinthGameLib/PathState.h 
        LabyrinthGameLib/GameBoardPlacedTokenMediator.cpp 
        LabyrinthGameLib/GameBoardPlacedTokenMediator.h
        LabyrinthGameLib/Game.h
        LabyrinthGameLib/Game.cpp
        LabyrinthGameLib/GameRules.h
        LabyrinthGameLib/GameRules.cpp)

set_project_warnings(LabyrinthGameLib)

add_executable(Hackathon_2021 main.cpp)
set_project_warnings(Hackathon_2021)


target_link_libraries(
        Hackathon_2021 
        LabyrinthGameLib 
        GraphLib 
        LoggerLib)
