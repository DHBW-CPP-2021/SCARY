#include "Maze.h"
#include "Utils/Utils.h"

namespace LabyrinthGame
{
    using namespace LabyrinthGame::GameSettings;
    using namespace LabyrinthGame::Geo;

    MazePiece const &Maze::getPiece(Coordinate const &coordinate) const
    {
        assert(Utils::isValid(coordinate));
        return _pieces[_piece_placement[Utils::compute1DFrom2D(coordinate)]];
    }

    MazePiece const &Maze::getSparePiece(GameSettings::CoordType const spare_piece_id) const
    {
        assert(spare_piece_id < NUM_SPARE_PIECES);
        return _pieces[_piece_placement[NUM_COORDINATES + spare_piece_id]];
    }

    bool Maze::isFixed(Coordinate const &coordinate) const
    {
        return _is_fixed.at(Utils::compute1DFrom2D(coordinate));
    }

    void Maze::fixMazePiece(Coordinate const &coordinate)
    {
        setFixation(coordinate, true);
    }

    void Maze::unfixMazePiece(Coordinate const &coordinate)
    {
        setFixation(coordinate, false);
    }

    void Maze::setFixation(Coordinate const &coordinate, bool b)
    {
        assert(Utils::isValid(coordinate));
        _is_fixed.at(Utils::compute1DFrom2D(coordinate)) = b;
    }

    Maze::Maze(std::vector<MazePiece> const &pieces_)
        : _pieces(pieces_), _piece_placement(), _is_fixed(NUM_COORDINATES, false)
    {
        assert(pieces_.size() == TOTAL_NUM_PIECES);
        // We stick the the order of _pieces for the beginning
        _piece_placement.reserve(TOTAL_NUM_PIECES);
        for (CoordType i = 0; i < TOTAL_NUM_PIECES; ++i)
        {
            _piece_placement.push_back(i);
        }
    }

    bool Maze::isRowFixed(GameSettings::CoordType y) const
    {
        for (GameSettings::CoordType x = 0; x < WIDTH; ++x)
        {
            if (isFixed({x, y}))
            {
                return true;
            }
        }
        return false;
    }

    bool Maze::isColumnFixed(GameSettings::CoordType x) const
    {
        for (GameSettings::CoordType y = 0; y < HEIGHT; ++y)
        {
            if (isFixed({x, y}))
            {
                return true;
            }
        }
        return false;
    }

    void Maze::insertSparePieceInRow(GameSettings::CoordType y, Direction d, GameSettings::CoordType _spare_piece_id)
    {
        assert(y < HEIGHT);
        assert(d == Direction::left || d == Direction::right);
        assert(_spare_piece_id < NUM_SPARE_PIECES);
        assert(!isRowFixed(y));
        if (d == Direction::right)
        {
            insertMazePieceOnTheLeft(_spare_piece_id, y);
        }
        else // direction = left
        {
            insertMazePieceOnTheRight(_spare_piece_id, y);
        }
    }

    void Maze::insertMazePieceOnTheLeft(LabyrinthGame::GameSettings::CoordType _spare_piece_id,
                                        LabyrinthGame::GameSettings::CoordType y)
    {
        CoordType const sparePieceTemp = _piece_placement[NUM_COORDINATES + _spare_piece_id];
        _piece_placement[NUM_COORDINATES + _spare_piece_id] =
            _piece_placement[Utils::compute1DFrom2D({static_cast<CoordType>(WIDTH - 1), y})];
        for (CoordType x = 1; x < WIDTH; ++x)
        {
            _piece_placement[Utils::compute1DFrom2D({static_cast<CoordType>(WIDTH - x), y})] =
                _piece_placement[Utils::compute1DFrom2D({static_cast<CoordType>(WIDTH - 1 - x), y})];
        }
        _piece_placement[Utils::compute1DFrom2D({0, y})] = sparePieceTemp;
    }

    void Maze::insertMazePieceOnTheRight(LabyrinthGame::GameSettings::CoordType _spare_piece_id,
                                         LabyrinthGame::GameSettings::CoordType y)
    {
        CoordType const sparePieceTemp = _piece_placement[NUM_COORDINATES + _spare_piece_id];
        _piece_placement[NUM_COORDINATES + _spare_piece_id] = _piece_placement[Utils::compute1DFrom2D({0, y})];
        for (CoordType x = 0; x < WIDTH - 1; ++x)
        {
            _piece_placement[Utils::compute1DFrom2D({x, y})] =
                _piece_placement[Utils::compute1DFrom2D({static_cast<CoordType>(x + 1), y})];
        }
        _piece_placement[Utils::compute1DFrom2D({WIDTH - 1, y})] = sparePieceTemp;
    }

    void Maze::insertMazePieceAtTheTop(LabyrinthGame::GameSettings::CoordType _spare_piece_id,
                                       LabyrinthGame::GameSettings::CoordType x)
    {
        CoordType const tmp = _piece_placement[NUM_COORDINATES + _spare_piece_id];
        _piece_placement[NUM_COORDINATES + _spare_piece_id] = _piece_placement[Utils::compute1DFrom2D({x, HEIGHT - 1})];
        for (CoordType y = 1; y < HEIGHT; ++y)
        {
            _piece_placement[Utils::compute1DFrom2D({x, static_cast<CoordType>(HEIGHT - y)})] =
                _piece_placement[Utils::compute1DFrom2D({x, static_cast<CoordType>(HEIGHT - 1 - y)})];
        }
        _piece_placement[Utils::compute1DFrom2D({x, 0})] = tmp;
    }

    void Maze::insertMazePieceAtTheBottom(LabyrinthGame::GameSettings::CoordType _spare_piece_id,
                                          LabyrinthGame::GameSettings::CoordType x)
    {
        CoordType const tmp = _piece_placement[NUM_COORDINATES + _spare_piece_id];
        _piece_placement[NUM_COORDINATES + _spare_piece_id] = _piece_placement[Utils::compute1DFrom2D({x, 0})];
        for (CoordType y = 0; y < HEIGHT - 1; ++y)
        {
            _piece_placement[Utils::compute1DFrom2D({x, static_cast<CoordType>(y)})] =
                _piece_placement[Utils::compute1DFrom2D({x, static_cast<CoordType>(y + 1)})];
        }
        _piece_placement[Utils::compute1DFrom2D({x, HEIGHT - 1})] = tmp;
    }

    void Maze::insertSparePieceInColumn(GameSettings::CoordType x, Direction d, GameSettings::CoordType _spare_piece_id)
    {
        assert(x < WIDTH);
        assert(d == Direction::up || d == Direction::down);
        assert(_spare_piece_id < NUM_SPARE_PIECES);
        assert(!isColumnFixed(x));
        // Store the actual piece id (in _pieces) in a tmp variable
        if (d == Direction::down)
        {
            insertMazePieceAtTheTop(_spare_piece_id, x);
        }
        else // direction = up
        {
            insertMazePieceAtTheBottom(_spare_piece_id, x);
        }
    }

} // namespace LabyrinthGame
