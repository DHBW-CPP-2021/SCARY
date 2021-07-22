#ifndef HACKATHON_2021_SPAREPIECEORACLE_H
#define HACKATHON_2021_SPAREPIECEORACLE_H

#include "../../GameBoard.h"
#include "MazePieceOracle.h"


namespace LabyrinthGame
{
    namespace IO
    {
        class SparePieceOracle : public MazePieceOracle
        {
        public:
            SparePieceOracle(const Maze &maze);

            GameSettings::CoordType numPieces() const override;

            const MazePiece &getMazePiece(GameSettings::CoordType id) const override;

            bool isFixed(GameSettings::CoordType id) const override;

            bool isTokenPlaced(GameSettings::CoordType id) const override;

            const Token &getPlacedToken(GameSettings::CoordType id) const override;

        private:
            Maze const &_maze;
        };
    } // namespace IO
} // namespace LabyrinthGame

#endif // HACKATHON_2021_SPAREPIECEORACLE_H
