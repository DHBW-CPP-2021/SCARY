#include "GameBoard.h"
#include "Utils/Utils.h"
#include <random>


namespace LabyrinthGame
{

    using namespace LabyrinthGame::GameSettings;
    using namespace LabyrinthGame::Geo;

    ///////
    /// Init static member
    GameBoard::Logger GameBoard::_logger;

    Maze const &LabyrinthGame::GameBoard::getMaze() const
    {
        return _maze;
    }

    GameBoard::Graph const &LabyrinthGame::GameBoard::getGraph() const
    {
        return _graph;
    }

    GameBoard::GameBoard()
        : _maze_pieces(initiallyCreateMazePieces()), _registered_token(), _maze(_maze_pieces),
          _graph(GameSettings::NUM_COORDINATES + 1)
    {
        setInitialMazeFixation();
        initiallyBuildGraphFromMaze();
    }

    GameBoard::Vertex const &GameBoard::getVertex(Coordinate const &coordinate) const
    {
        assert(Utils::isValid(coordinate));
        return _graph.getVertex(Utils::compute1DFrom2D(coordinate));
    }

    GameBoard::Vertex &GameBoard::getVertex(const Coordinate &coordinate)
    {
        return const_cast<Vertex &>(static_cast<GameBoard const *>(this)->getVertex(coordinate));
    }

    GameBoard::Vertex const &GameBoard::getOutsideVertex() const
    {
        return _graph.getVertex(_graph.numVertices() - 1);
    }

    GameBoard::Vertex &GameBoard::getOutsideVertex()
    {
        return const_cast<Vertex &>(static_cast<GameBoard const *>(this)->getOutsideVertex());
    }

    MazePiece const &GameBoard::getMazePiece(const Coordinate &coordinate) const
    {
        assert(Utils::isValid(coordinate));
        return _maze.getPiece(coordinate);
    }

    MazePiece &GameBoard::getMazePiece(const Coordinate &coordinate)
    {
        return const_cast<MazePiece &>(static_cast<GameBoard const *>(this)->getMazePiece(coordinate));
    }

    void GameBoard::initiallyBuildGraphFromMaze()
    {
        assert(_graph.numVertices() == static_cast<VertexId>(NUM_COORDINATES + 1));
        assert(_graph.numEdges() == 0);
        for (CoordType x = 0; x < WIDTH; ++x)
        {
            updateGraphAccordingToRowChanges(x);
        }
    }

    void GameBoard::updateGraphAccordingToColumnChanges(CoordType x)
    {
        assert(x < GameSettings::WIDTH);
        for (CoordType y = 0; y < GameSettings::HEIGHT; ++y)
        {
            updateCoordinate({x, y});
        }
    }

    void GameBoard::updateGraphAccordingToRowChanges(CoordType y)
    {
        assert(y < GameSettings::HEIGHT);
        for (CoordType x = 0; x < GameSettings::WIDTH; ++x)
        {
            updateCoordinate(Coordinate(x, y));
        }
    }

    void addEdgeIfTrueRemoveOtherwise(Combinatorics::Graph &g, Combinatorics::Vertex &v, Combinatorics::Vertex &w,
                                      bool condition)
    {
        if (condition)
        {
            g.addEdgeIfNonexistent(v, w);
        }
        else
        {
            g.removeEdgeIfExistent(v, w);
        }
    }

    void GameBoard::updateCoordinate(const Coordinate &c)
    {
        assert(c.getX() < GameSettings::WIDTH);
        assert(c.getY() < GameSettings::HEIGHT);
        MazePiece const &p = getMazePiece(c);
        Vertex &v = getVertex(c);

        for (Direction d : {Direction::up, Direction::down, Direction::left, Direction::right})
        {
            Coordinate const neighborCord = c.adjacentCoordinate(d);
            addEdgeIfTrueRemoveOtherwise(_graph, v,
                                         // All positions outside the maze are modelled by a single target value
                                         Utils::isValid(neighborCord) ? getVertex(neighborCord) : getOutsideVertex(),
                                         mazeConfigurationImpliesEdge(c, neighborCord, d));
        }
        // We have to consider the corner cases explicitly. Otherwise it could be that we add - for example -
        // an edge for the lower left corner since it is open to the down and remove these edge the next step
        // since the way is blocked to the left
        if (c.getX() == 0)
        {
            if (c.getY() == 0)
            {
                addEdgeIfTrueRemoveOtherwise(_graph, v, getOutsideVertex(),
                                             p.isOpen(Direction::left) || p.isOpen(Direction::up));
            }
            else if (c.getY() == GameSettings::HEIGHT - 1)
            {
                addEdgeIfTrueRemoveOtherwise(_graph, v, getOutsideVertex(),
                                             p.isOpen(Direction::left) || p.isOpen(Direction::down));
            }
        }
        else if (c.getX() == GameSettings::WIDTH - 1)
        {
            if (c.getY() == 0)
            {
                addEdgeIfTrueRemoveOtherwise(_graph, v, getOutsideVertex(),
                                             p.isOpen(Direction::right) || p.isOpen(Direction::up));
            }
            else if (c.getY() == GameSettings::HEIGHT - 1)
            {
                addEdgeIfTrueRemoveOtherwise(_graph, v, getOutsideVertex(),
                                             p.isOpen(Direction::right) || p.isOpen(Direction::down));
            }
        }
    }

    void GameBoard::setInitialMazeFixation()
    {
        for (CoordType x = 0; x < WIDTH; x += 2)
        {
            for (CoordType y = 0; y < HEIGHT; y += 2)
            {
                _maze.fixMazePiece({x, y});
            }
        }
    }

    bool GameBoard::mazeConfigurationImpliesEdge(Coordinate const &c, Coordinate neighbor, Direction d) const
    {
        assert(Utils::isValid(c));
        assert(c.adjacentCoordinate(d) == neighbor);
        MazePiece const &p = getMazePiece(c);
        /*
         * We add an edge if p is open in direction d (e.g. to to right) and the neighbor in direction d
         * (e.g. the right neighbor) is open to the opposite direction (e.g. to the left). In the special
         * case that p is an border coordinate and direction d points out of the field the neighbor
         * coordinate will be invalid and imply no restrictions
         */
        return p.isOpen(d) && (Utils::isValid(neighbor) ? getMazePiece(neighbor).isOpen(oppositeDirection(d)) : true);
    }

    std::vector<MazePiece> GameBoard::initiallyCreateMazePieces() const
    {
        // TODO: Pure randomness is maybe not the best idea for an game, is it?
        // Create random generator
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(0, 1.);
        std::uniform_int_distribution<> int_dis(0, 3);

        std::vector<MazePiece> v;
        v.reserve(GameSettings::TOTAL_NUM_PIECES);
        for (CoordType i = 0; i < GameSettings::TOTAL_NUM_PIECES; ++i)
        {
            std::vector<bool> b;
            for (unsigned k = 0; k < 4; ++k)
            {
                b.push_back(dis(gen) < OPEN_PROBABILITY);
            }
            // maybe we have to open one side
            if (!(b[0] || b[0] || b[2] || b[3]))
            {
                b[int_dis(gen)] = true;
            }
            PathState const PathState1 = b[0] ? PathState::open : PathState::closed;
            PathState const PathState2 = b[1] ? PathState::open : PathState::closed;
            PathState const PathState3 = b[2] ? PathState::open : PathState::closed;
            PathState const PathState4 = b[3] ? PathState::open : PathState::closed;
            v.emplace_back(PathState1, PathState2, PathState3, PathState4);
        }
        return v;
    }

    bool GameBoard::isTokenPlaced(Coordinate const &coordinate) const
    {
        auto search = [&coordinate](PlacedToken const *t) { return t->getCoordinate() == coordinate; };
        return std::find_if(_registered_token.begin(), _registered_token.end(), search) != _registered_token.end();
    }

    PlacedToken &GameBoard::getToken(Coordinate const &coordinate) const
    {
        assert(isTokenPlaced(coordinate));
        auto search = [&coordinate](PlacedToken const *t) { return t->getCoordinate() == coordinate; };
        return **std::find_if(_registered_token.begin(), _registered_token.end(), search);
    }

    void GameBoard::insertSparePieceInRow(GameSettings::CoordType y, Direction direction,
                                          GameSettings::CoordType _spare_piece_id)
    {
        assert(direction == Direction::left || direction == Direction::right);
        _maze.insertSparePieceInRow(y, direction, _spare_piece_id);
        notifyPlacedTokenAboutRowMovement(y, direction);
        updateGraphAccordingToRowChanges(y);
    }

    void GameBoard::insertSparePieceInColumn(GameSettings::CoordType x, Direction direction,
                                             GameSettings::CoordType _spare_piece_id)
    {
        assert(direction == Direction::up || direction == Direction::down);
        _maze.insertSparePieceInColumn(x, direction, _spare_piece_id);
        notifyPlacedTokenAboutColumnMovement(x, direction);
        updateGraphAccordingToColumnChanges(x);
    }

    void GameBoard::notifyPlacedTokenAboutRowMovement(GameSettings::CoordType y, Direction direction)
    {
        assert(direction == Direction::left || direction == Direction::right);
        for (PlacedToken *t : _registered_token)
        {
            if (t->getCoordinate().getY() == y)
            {
                GameBoardPlacedTokenMediator::notifyMovement(*t, direction);
            }
        }
    }

    void GameBoard::notifyPlacedTokenAboutColumnMovement(GameSettings::CoordType x, Direction direction)
    {
        assert(direction == Direction::up || direction == Direction::down);
        for (PlacedToken *t : _registered_token)
        {
            if (t->getCoordinate().getX() == x)
            {
                GameBoardPlacedTokenMediator::notifyMovement(*t, direction);
            }
        }
    }

    void GameBoard::registerToken(PlacedToken *token)
    {
        _registered_token.push_back(token);
    }
} // namespace LabyrinthGame
