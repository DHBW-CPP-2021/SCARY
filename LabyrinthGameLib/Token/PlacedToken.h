#ifndef HACKATHON_2021_PLACEDTOKEN_H
#define HACKATHON_2021_PLACEDTOKEN_H
#include "../GameBoardPlacedTokenMediator.h"
#include "../Geo/Coordinate.h"
#include "../IO/Token.h"

namespace LabyrinthGame
{
    // Forward declaration
    class GameBoard;

    /**
     * A placed token is an abstract class symbolizing an token placed somewhere at a GameBoard
     * It will register itself to GameBoard during its creation, which will keep a pointer to the token.
     * Therefore it is crucial that tokens are managed with stable memory
     */
    class PlacedToken : public IO::Token
    {
        using Coordinate = Geo::Coordinate;

    public:
        explicit PlacedToken(GameBoard &_board, TokenArrayMatrix const &character_representation);
        explicit PlacedToken(GameBoard &_board, char single_char_representation);

        // A placed token should be able to communicate its coordinates
        virtual Coordinate getCoordinate() const = 0; // todo should this be implemented?

    protected:
        friend class GameBoardPlacedTokenMediator;
        /**
         * The GameBoard (and only the GameBoard) can notify a PlacedToken about the movement of the underlying
         * MazePiece. It depends on your token whether and how it uses this information.
         * @param d The direction in which the underlying maze piece moves
         */
        virtual void notifyMovement(Geo::Direction d) = 0;
    };

} // namespace LabyrinthGame

#endif // HACKATHON_2021_PLACEDTOKEN_H
