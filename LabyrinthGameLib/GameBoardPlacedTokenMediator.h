#ifndef HACKATHON_2021_GAMEBOARDPLACEDTOKENMEDIATOR_H
#define HACKATHON_2021_GAMEBOARDPLACEDTOKENMEDIATOR_H
#include "Geo/Direction.h"

namespace LabyrinthGame
{
    // Forward declaration
    class PlacedToken;
    class GameBoard;

    /**
     * This class is only used to provide GameBoard and PlacedToken (friend) access to
     * individually chosen provide methods
     */
    class GameBoardPlacedTokenMediator
    {
        friend class GameBoard;
        friend class PlacedToken;

    private:
        static void registerToken(PlacedToken *token, GameBoard &board);
        static void notifyMovement(PlacedToken &token, Geo::Direction d);
    };

} // namespace LabyrinthGame

#endif // HACKATHON_2021_GAMEBOARDPLACEDTOKENMEDIATOR_H
