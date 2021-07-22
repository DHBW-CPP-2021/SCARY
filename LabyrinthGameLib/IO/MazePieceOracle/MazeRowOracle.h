#ifndef HACKATHON_2021_MAZEROWORACLE_H
#define HACKATHON_2021_MAZEROWORACLE_H

#include "../../GameBoard.h"
#include "../../Maze.h"
#include "../Token.h"
#include "MazePieceOracle.h"


namespace LabyrinthGame
{
    namespace IO
    {
        class MazeRowOracle : public MazePieceOracle
        {
            using Coordinate = Geo::Coordinate;

        public:
            MazeRowOracle(GameBoard const &board_, GameSettings::CoordType y_);

            GameSettings::CoordType numPieces() const override;

            MazePiece const &getMazePiece(GameSettings::CoordType x) const override;

            bool isFixed(GameSettings::CoordType id) const override;

            bool isTokenPlaced(GameSettings::CoordType id) const override;

            const Token &getPlacedToken(GameSettings::CoordType id) const override;

        private:
            GameBoard const &_board;
            GameSettings::CoordType const _y;

            // Returns coordinate for an given x value
            Coordinate coord(GameSettings::CoordType x) const;
        };
    } // namespace IO
} // namespace LabyrinthGame

#endif // HACKATHON_2021_MAZEROWORACLE_H
