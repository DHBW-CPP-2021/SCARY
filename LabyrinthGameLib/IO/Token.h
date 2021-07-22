#ifndef HACKATHON_2021_TOKEN_H
#define HACKATHON_2021_TOKEN_H
#include "../IO/DrawingConst.h"
#include <array>


namespace LabyrinthGame::IO
{

    /**
     * A token represents a game figure, a reward or something similar, which can be placed on the game field.
     * This class encapsulates only the visual properties of a token and will be used by the GameDrawer.
     */
    class Token
    {
    public:
        // Improve readability
        using TokenArrayRow = std::array<char, DrawingConst::inner_width>;
        using TokenArrayMatrix = std::array<TokenArrayRow, DrawingConst::inner_height>;

        // If you want you can specify the appearance of your token on the whole inner_width x inner_height Matrix
        explicit Token(TokenArrayMatrix const &character_representation_);

        // You can represent a token by a single character
        explicit Token(char single_char_representation);

        [[nodiscard]] const TokenArrayMatrix &getCharacterRepresentation() const;

        /**
         * You may want to use multiple character token representation.
         * This methods gives you an empty representation matrix you can fill like you want
         * @return
         */
        static TokenArrayMatrix getEmptyTokenArrayMatrix();

    private:
        TokenArrayMatrix _character_representation;
    };
} // namespace LabyrinthGame::IO

#endif // HACKATHON_2021_TOKEN_H
