#include "GameDrawer.h"
#include "MazePieceOracle/MazeRowOracle.h"
#include "MazePieceOracle/SparePieceOracle.h"
#include <cmath>


namespace LabyrinthGame
{
    namespace IO
    {
        using namespace LabyrinthGame::GameSettings;
        using namespace LabyrinthGame::Geo;

        GameDrawer::GameDrawer(GameBoard const &board_) : _board(board_), preComputed()
        {
        }

        std::array<char const, 15> digits{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o'};

        std::string to_alph_numbering(unsigned int k)
        {
            return std::string(1, digits.at(k));
        }

        void GameDrawer::drawMaze(std::ostream &out) const
        {
            // Create IO Configuration (drawing to out, no whitespaces)
            IO io(out, 0, 0);

            draw_x_axis(io, WIDTH);

            // It's a loop's world
            // First we loop over all rows
            for (GameSettings::CoordType y = 0; y < HEIGHT; ++y)
            {
                // Create an Oracle grouping the MazePieces of a row
                MazeRowOracle oracle(_board, y);
                draw_line_of_pieces(io, oracle, to_alph_numbering(y));
                draw_whitespace_between_rows(io);
            }
            // Finally draw another x-axis
            draw_x_axis(io, WIDTH);
        }

        void GameDrawer::draw_upper_lower_wall_part(IO &io, MazePieceOracle const &oracle, Direction d) const
        {
            assert(d == Direction::up || d == Direction::down);
            for (GameSettings::CoordType k = 0; k < oracle.numPieces(); ++k)
            {
                draw_upper_lower_wall_part(io, oracle.getMazePiece(k), oracle.isFixed(k), d);
            }
        }

        void GameDrawer::draw_upper_lower_wall_part(IO &io, MazePiece const &p, bool is_fixed, Direction d) const
        {
            assert(d == Direction::up || d == Direction::down);
            std::string const &corner = preComputed._left_right_free;
            io.out << corner;
            if (p.isClosed(d))
            {
                io.out << (is_fixed ? preComputed._upper_lower_fixed_wall : preComputed._upper_lower_wall);
            }
            else
            {
                io.out << preComputed._upper_lower_free;
            }
            io.out << corner;
            draw_whitespace_between_columns(io);
        }

        void GameDrawer::draw_left_right_inner_part(IO &io, bool isClosed, bool isFixed) const
        {
            if (isClosed)
            {
                io.out << (isFixed ? preComputed._left_right_fixed_wall : preComputed._left_right_wall);
            }
            else
            {
                io.out << preComputed._left_right_free;
            }
        }

        void GameDrawer::draw_center_of_inner_part(IO &io, MazePieceOracle const &oracle, unsigned short inner_y,
                                                   CoordType k) const
        {
            if (oracle.isTokenPlaced(k))
            {
                Token const &token = oracle.getPlacedToken(k);
                for (char const &c : token.getCharacterRepresentation()[inner_y])
                {
                    io.out << c;
                }
            }
            else
            {
                io.out << preComputed._inner_space;
            }
        }

        void GameDrawer::draw_inner_part(IO &io, MazePieceOracle const &oracle, unsigned short inner_y) const
        {
            for (GameSettings::CoordType k = 0; k < oracle.numPieces(); ++k)
            {
                MazePiece const &p = oracle.getMazePiece(k);
                draw_left_right_inner_part(io, p.isClosed(Direction::left), oracle.isFixed(k));
                draw_center_of_inner_part(io, oracle, inner_y, k);
                draw_left_right_inner_part(io, p.isClosed(Direction::right), oracle.isFixed(k));
                draw_whitespace_between_columns(io);
            }
        }

        unsigned short GameDrawer::wallWidth()
        {
            return DrawingConst::wall_width;
        }

        unsigned short GameDrawer::wallHeight()
        {
            return DrawingConst::wall_height;
        }

        unsigned short GameDrawer::innerWidth()
        {
            return DrawingConst::inner_width;
        }

        unsigned short GameDrawer::innerHeight()
        {
            return DrawingConst::inner_height;
        }

        unsigned short GameDrawer::pieceWidth()
        {
            return innerWidth() + 2 * wallWidth();
        }

        unsigned short GameDrawer::pieceHeight()
        {
            return innerHeight() + 2 * wallHeight();
        }

        unsigned short GameDrawer::rowLabelSpacing()
        {
            return DrawingConst::row_label_spacing;
        }

        void GameDrawer::drawSparePieces(std::ostream &out, bool label_pieces) const
        {
            SparePieceOracle oracle(_board.getMaze());
            IO io(out, 5, 0);
            draw_line_of_pieces(io, oracle);
            if (label_pieces)
            {
                draw_x_axis(io, oracle.numPieces());
            }
        }

        void GameDrawer::draw_line_of_pieces(IO &io, const MazePieceOracle &oracle, std::string const &label) const
        {
            // We will display the label centered and add blanks at every other line
            std::string const blanks(label.size(), ' ');
            std::string const spacing_blanks(rowLabelSpacing(), ' ');
            auto const center_coord = static_cast<unsigned short>(std::round(pieceHeight() / 2));

            // k counts the inner rows (i.e. upper part, middle part, lower part) of the line of maze pieces
            unsigned short k;
            // upper wall part of MazePiece row
            for (k = 0; k < wallHeight(); ++k)
            {
                io.out << blanks << spacing_blanks;
                draw_upper_lower_wall_part(io, oracle, Direction::up);
                io.out << "\n";
            }
            // inner part of MazePiece row
            for (; k < wallHeight() + innerHeight(); ++k)
            {
                io.out << (k == center_coord ? label : blanks) << spacing_blanks;
                draw_inner_part(io, oracle, k - wallHeight());
                io.out << spacing_blanks << (k == center_coord ? label : blanks) << "\n";
            }
            // lower wall part of MazePiece row
            for (; k < 2 * wallHeight() + innerHeight(); ++k)
            {
                io.out << blanks << spacing_blanks;
                draw_upper_lower_wall_part(io, oracle, Direction::down);
                io.out << "\n";
            }
            std::cout << std::flush;
        }

        void GameDrawer::draw_whitespace_between_columns(GameDrawer::IO &io)
        {
            for (GameSettings::CoordType w = 0; w < io.whitespace_between_columns; ++w)
            {
                io.out << " ";
            }
        }

        void GameDrawer::draw_whitespace_between_rows(GameDrawer::IO &io)
        {
            for (GameSettings::CoordType w = 0; w < io.whitespace_between_rows; ++w)
            {
                io.out << "\n";
            }
        }

        void GameDrawer::draw_x_axis(GameDrawer::IO &io, GameSettings::CoordType num_labels)
        {
            std::string const initial_blanks(static_cast<size_t>(std::floor(pieceWidth() / 2.)) + rowLabelSpacing(), ' ');
            std::string const blanks_between_pieces(pieceWidth() - 1 + io.whitespace_between_columns, ' ');
            io.out << initial_blanks;
            for (CoordType k = 0; k < num_labels; ++k)
            {
                io.out << k << blanks_between_pieces;
            }
            io.out << "\n";
        }

        GameDrawer::PreparedStrings::PreparedStrings()
            : _upper_lower_wall(GameDrawer::innerWidth(), '-'), _upper_lower_fixed_wall(GameDrawer::innerWidth(), '*'),
              _upper_lower_free(GameDrawer::innerWidth(), ' '), _left_right_wall(GameDrawer::wallWidth(), '|'),
              _left_right_fixed_wall(GameDrawer::wallWidth(), '*'), _left_right_free(GameDrawer::wallWidth(), ' '),
              _inner_space(GameDrawer::innerWidth(), ' ')
        {
        }

        GameDrawer::IO::IO(std::ostream &out, GameSettings::CoordType whitespace_between_columns_,
                           GameSettings::CoordType whitespace_between_rows_)
            : out(out), whitespace_between_columns(whitespace_between_columns_),
              whitespace_between_rows(whitespace_between_rows_)
        {
        }

    } // namespace IO
} // namespace LabyrinthGame
