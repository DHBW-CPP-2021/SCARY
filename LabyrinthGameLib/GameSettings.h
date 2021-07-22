#ifndef HACKATHON_2021_GAMESETTINGS_H
#define HACKATHON_2021_GAMESETTINGS_H

namespace LabyrinthGame
{
    namespace GameSettings
    {
        using CoordType = unsigned short;
        CoordType constexpr WIDTH = 7;
        CoordType constexpr HEIGHT = 7;
        CoordType constexpr NUM_COORDINATES = WIDTH * HEIGHT;
        CoordType constexpr NUM_SPARE_PIECES = 3;
        CoordType constexpr TOTAL_NUM_PIECES = NUM_COORDINATES + NUM_SPARE_PIECES;
        // Probability that a random MazePiece is open in a given direction.
        // Mathematically speaking that's not really the probability for one side to be open, since we choose
        // independently for every side if it's open with probability OPEN_PROBABILITY.
        // But, if all 4 sides are closed we open a randomly chosen side.
        double constexpr OPEN_PROBABILITY = 0.55;
    } // namespace GameSettings
} // namespace LabyrinthGame

#endif // HACKATHON_2021_GAMESETTINGS_H
