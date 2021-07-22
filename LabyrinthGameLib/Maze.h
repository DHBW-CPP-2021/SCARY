#ifndef HACKATHON_2021_MAZE_H
#define HACKATHON_2021_MAZE_H

#include "GameSettings.h"
#include "Geo/Coordinate.h"
#include "MazePiece.h"
#include <cassert>
#include <iostream>
#include <vector>


namespace LabyrinthGame
{

    /**
     * The class maze stores information about the placement and fixation of the MazePieces
     * It does NOT own the MazePieces (all game equipment should be owned by the GameBoard)
     */
    class Maze
    {
        using Coordinate = Geo::Coordinate;

    public:
        /**
         * You can build a maze by passing  a container with NUM_MAZE_PIECES MazePieces
         * @param pieces_ the vector containing the MazePieces
         */
        explicit Maze(std::vector<MazePiece> const &pieces_);

        Maze operator=(const Maze &other) = delete;
        Maze(const Maze &other) = delete;

        /**
         * Returns a piece inside the maze
         * @param coordinate
         * @return MazePiece placed at a specific coordinate
         */
        [[nodiscard]] MazePiece const &getPiece(Coordinate const &coordinate) const;

        /**
         * Returns on of the NUM_SPARE_PIECES many spare pieces
         * @param spare_piece_id
         * @return MazePiece currently not placed inside the maze
         */
        [[nodiscard]] MazePiece const &getSparePiece(GameSettings::CoordType spare_piece_id) const;

        /**
         * Returns true iff the maze piece is fixed (i.e. not movable)
         * @param coordinate
         * @return true iff fixed
         */
        [[nodiscard]] bool isFixed(Coordinate const &coordinate) const;

        /**
         * Checks whether a row is fixed or not. A row is fixed if and only if at least one coordinate in the row
         * is fixed
         * @param y The row index
         * @return true iff the row is fixed
         */
        [[nodiscard]] bool isRowFixed(GameSettings::CoordType y) const;

        /**
         * Checks whether a column is fixed or not. A column is fixed if and only if at least one coordinate in the
         * columnis fixed
         * @param x The column
         * @return true iff the column is fixed
         */
        [[nodiscard]] bool isColumnFixed(GameSettings::CoordType x) const;

        /**
         * Inserts a spare piece to the maze from left or right
         * @param y The row the spare piece is added to
         * @param d The direction (left, right) we add the piece to. If direction is right, we add the piece from
         * the left
         * @param _spare_piece_id The id according to \a getSparePiece
         */
        void insertSparePieceInRow(GameSettings::CoordType y, Geo::Direction d, GameSettings::CoordType spare_piece_id);

        /**
         * Inserts a spare piece to the maze from top or bottom
         * @param x The column the spare piece is added to
         * @param d The direction (up, down) we add the piece to. If direction is up, we add the piece from
         * the bottom
         * @param _spare_piece_id The id according to \a getSparePiece
         */
        void insertSparePieceInColumn(GameSettings::CoordType x, Geo::Direction d, GameSettings::CoordType spare_piece_id);

        /**
         * Fixate a maze piece at a given position
         * @param coordinate
         */
        void fixMazePiece(Coordinate const &coordinate);

        /**
         * Unfix a maze piece at a given coordinate
         * @param coordinate
         */
        void unfixMazePiece(Coordinate const &coordinate);

        /**
         * Fixes or unfixes a MazePiece at a given Coordinate
         * @param coordinate
         * @param b
         */
        void setFixation(Coordinate const &coordinate, bool b);

    private:
        // The actual maze pieces
        std::vector<MazePiece> const &_pieces;
        void insertMazePieceOnTheLeft(LabyrinthGame::GameSettings::CoordType _spare_piece_id,
                                      LabyrinthGame::GameSettings::CoordType y);
        void insertMazePieceOnTheRight(LabyrinthGame::GameSettings::CoordType _spare_piece_id,
                                       LabyrinthGame::GameSettings::CoordType y);
        void insertMazePieceAtTheTop(LabyrinthGame::GameSettings::CoordType _spare_piece_id,
                                     LabyrinthGame::GameSettings::CoordType x);
        void insertMazePieceAtTheBottom(LabyrinthGame::GameSettings::CoordType _spare_piece_id,
                                        LabyrinthGame::GameSettings::CoordType x);

        /*
         * The actual placement of the _pieces inside the maze. _piece_placement[n]== m means that the m-th piece is
         * placed at the n-th position of the maze. NUM_COORDINATES, NUM_COORDINATES + 1 , ...,
         * NUM_COORDINATES+NUM_SPARE_PIECES-1 are the indices of spare pieces
         *
         * Mathematically speaking _piece_placement is a permutation function for _pieces ;)
         */
        std::vector<GameSettings::CoordType> _piece_placement;
        std::vector<bool> _is_fixed;
    };

} // namespace LabyrinthGame

#endif // HACKATHON_2021_MAZE_H
