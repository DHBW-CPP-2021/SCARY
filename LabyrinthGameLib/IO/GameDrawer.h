#ifndef HACKATHON_2021_GAMEDRAWER_H
#define HACKATHON_2021_GAMEDRAWER_H

#include "../GameBoard.h"
#include "DrawingConst.h"
#include "MazePieceOracle/MazePieceOracle.h"
#include <iostream>


namespace LabyrinthGame
{
    namespace IO
    {
        class GameDrawer
        {
        public:
            explicit GameDrawer(const GameBoard &board_);

            void drawMaze(std::ostream &out = std::cout) const;

            void drawSparePieces(std::ostream &out = std::cout, bool label_pieces = true) const;

            [[nodiscard]] static unsigned short wallWidth();

            [[nodiscard]] static unsigned short wallHeight();

            [[nodiscard]] static unsigned short innerWidth();

            [[nodiscard]] static unsigned short innerHeight();

            [[nodiscard]] static unsigned short pieceWidth();

            [[nodiscard]] static unsigned short pieceHeight();

            [[nodiscard]] static unsigned short rowLabelSpacing();

        private:
            GameBoard const &_board;

            // In order to simplify the drawing procedure we will pre-compute some possible parts of the final drawing.
            struct PreparedStrings
            {
                PreparedStrings();

                std::string const _upper_lower_wall;
                std::string const _upper_lower_fixed_wall;
                std::string const _upper_lower_free;
                std::string const _left_right_wall;
                std::string const _left_right_fixed_wall;
                std::string const _left_right_free;
                std::string const _inner_space;
            };

            PreparedStrings const preComputed;

            ////////////
            // Auxiliary

            struct IO
            {
                IO(std::ostream &out, GameSettings::CoordType whitespace_between_columns_,
                   GameSettings::CoordType whitespace_between_rows_);

                std::ostream &out;
                unsigned short whitespace_between_columns;
                unsigned short whitespace_between_rows;
            };

            // Draws a line of pieces according to an MazePieceOracle
            void draw_line_of_pieces(IO &io, MazePieceOracle const &oracle, std::string const &label = "") const;

            // Draws a row of the maze for a part with corresponds to the upper or lower end of a MazePiece
            void draw_upper_lower_wall_part(IO &io, MazePieceOracle const &oracle, Geo::Direction d) const;

            // Draws tje upper or lower end of a MazePiece
            void draw_upper_lower_wall_part(IO &io, MazePiece const &p, bool is_fixed, Geo::Direction d) const;

            // Draws an inner row of maze pieces according to a MazePieceOracle
            void draw_inner_part(IO &io, MazePieceOracle const &oracle, unsigned short inner_y) const;

            // draws the left/right part of an inner row of maze pieces
            void draw_left_right_inner_part(IO &io, bool isClosed, bool isFixed) const;

            // draws the center part of an inner row of maze pieces
            void draw_center_of_inner_part(IO &io, MazePieceOracle const &oracle, unsigned short inner_y,
                                           GameSettings::CoordType k) const;

            // Adds whitespace between columns as specified in IO
            static void draw_whitespace_between_columns(IO &io);

            // Adds whitespace between rows as specified in IO
            static void draw_whitespace_between_rows(IO &io);

            static void draw_x_axis(IO &io, GameSettings::CoordType num_labels);
        };
    } // namespace IO
} // namespace LabyrinthGame
#endif // HACKATHON_2021_GAMEDRAWER_H
