#ifndef HACKATHON_2021_GAMEBOARD_H
#define HACKATHON_2021_GAMEBOARD_H

#include "../Graph/Graph-commons.h"
#include "../Graph/Graph.h"
#include "GameSettings.h"
#include "Maze.h"
#include "Player/AbstractPlayer.h"
#include "Token/PlacedToken.h"
#include "Token/TreasureToken.h"

namespace LabyrinthGame
{

    class GameBoard
    {
        using Graph = Combinatorics::Graph;
        using Vertex = Combinatorics::Vertex;
        using VertexId = Combinatorics::VertexId;
        using Coordinate = Geo::Coordinate;
        // You can adapt the log level here...
        using Logger = DHBW_LOG::CoutLogger<LogLevel::DEBUG>;

    public:
        /**
         * Constructor.
         * TODO: You may want to extend this methode
         */
        explicit GameBoard();

        /**
         * Getter for the underlying maze
         * @return The underlying maze
         */
        [[nodiscard]] Maze const &getMaze() const;

        /**
         * Getter for the underlying graph. Each field (displayed as coordinate) corresponds
         * to a vertex of the graph. There is an edge between two vertices if and only if
         * both vertices are neighbours in the board game, i.e. they are directly adijazent
         * (share a boarder) and there is no wall between them.
         *
         * The graph can be used to use standard algorithms (like shortest path).
         * @return The underlying graph
         */
        [[nodiscard]] Graph const &getGraph() const;

        /**
         * Check whether a token is placed on a specific coordinate
         * @param coordinate
         * @return True iff a token is placed on this coordinate
         */
        [[nodiscard]] bool isTokenPlaced(Coordinate const &coordinate) const;

        /**
         * This method is unchecked - use isTokenPlaced to check whether a token is placed on a given position
         * @param coordinate
         * @return Token placed on coordinate
         */
        [[nodiscard]] PlacedToken &getToken(Coordinate const &coordinate) const;

        /**
         * Insert a spare piece into a given row. You can ask the underlying maze to see the spare pieces or use the
         * GameDrawer class to visualize them. We would be surprised if this function remains unused... :)
         * @param y Row index (top->down) starting with 0
         * @param direction Do you want to move the row to the left or to the right?
         * @param _spare_piece_id ID of the spare piece
         */
        [[maybe_unused]] void insertSparePieceInRow(GameSettings::CoordType y, Geo::Direction direction,
                                                    GameSettings::CoordType spare_piece_id);

        /**
         * Insert a spare piece into a given coulm. You can ask the underlying maze to see the spare pieces or use the
         * GameDrawer class to visualize them. We would be surprised if this function remains unused... :)
         * @param x column index (left->right) starting with 0
         * @param direction Do you want to move the row to the left or to the right?
         * @param _spare_piece_id ID of the spare piece
         */
        [[maybe_unused]] void insertSparePieceInColumn(GameSettings::CoordType x, Geo::Direction direction,
                                                       GameSettings::CoordType spare_piece_id);

        [[nodiscard]] bool coordsAreConnected(const Coordinate &coord1, const Coordinate &coord2) const;
        [[nodiscard]] bool coordIsConnectedToOutside(const Coordinate &coord) const;

        void setPlayers(const std::vector<std::shared_ptr<AbstractPlayer>> &players);
        [[nodiscard]] std::vector<std::shared_ptr<AbstractPlayer>> getPlayers() const;
        void setTreasures(const std::vector<std::shared_ptr<TreasureToken>> &treasures);
        [[nodiscard]] std::vector<std::shared_ptr<TreasureToken>> getTreasures() const;
        [[nodiscard]] std::vector<std::shared_ptr<TreasureToken>> &getTreasures();

    private:
        // Stable storage (after creation) of all available MazePieces
        std::vector<MazePiece> const _maze_pieces;
        // see methode registerToken
        std::vector<PlacedToken *> _registered_token;
        Maze _maze;
        Graph _graph;

        std::vector<std::shared_ptr<AbstractPlayer>> m_players;
        std::vector<std::shared_ptr<TreasureToken>> m_treasures;

        /**
         * TODO: You may want to change something here? (Not necessary)
         * Some pieces of the maze are fixated, right from the beginning.
         */
        void setInitialMazeFixation();

        /**
         * Register a token to the GameBoard. The game Board will hold an permanently pointer.
         *  Therefore it is crucial that token is stored with stable memory
         * @param token
         * TODO Attention! This method does NOT check whether there is already a token at the coordinate
         */
        void registerToken(PlacedToken *token);
        friend class GameBoardPlacedTokenMediator;

        /**
         * It's the objective of the game to leave the maze. All positions "outside"
         * of the maze are modelled be a single target vertex
         * @return The target vertex every player tries to reach
         */
        [[nodiscard]] Vertex const &getOutsideVertex() const;

        /**
         * It's the objective of the game to leave the maze. All positions "outside"
         * of the maze are modelled be a single target vertex
         * @return The target vertex every player tries to reach
         */
        [[nodiscard]] Vertex &getOutsideVertex();

        /**
         * Get Vertex at specific coordinate
         * @param coordinate
         * @return Vertex corresponding to coordinate or \a getOutsideVertex() if no Vertex corresponds
         * to the given coordinate
         */
        [[nodiscard]] Vertex &getVertex(Coordinate const &coordinate);

        /**
         * Get Vertex at specific coordinate
         * @param coordinate
         * @return Vertex corresponding to coordinate or \a getOutsideVertex() if no Vertex corresponds
         * to the given coordinate
         */
        [[nodiscard]] Vertex const &getVertex(Coordinate const &coordinate) const;

        /**
         * Get \a MazePiece at specific coordinate
         * @param coordinate
         * @return \a MazePiece currently corresponding to coordinate, or the \a _all_open_maze_piece if
         * no MazePiece corresponds to the given coordinate
         */
        [[nodiscard]] MazePiece &getMazePiece(Coordinate const &coordinate);

        /**
         * Get \a MazePiece at specific coordinate
         * @param coordinate
         * @return \a MazePiece currently corresponding to coordinate, or the \a _all_open_maze_piece if
         * no MazePiece corresponds to the given coordinate
         */
        [[nodiscard]] MazePiece const &getMazePiece(Coordinate const &coordinate) const;

        /**
         * Determines if there should be an edge beetween an coordinate c and its neighbor coordinate
         * @param c The coordinate
         * @param neighbor the neighbor coordinate
         * @param d the direction between c and neighbor
         * @return True if the maze configuration implies an edge beetween c and its neighbor in direction d
         */
        [[nodiscard]] bool mazeConfigurationImpliesEdge(Coordinate const &c, Coordinate neighbor, Geo::Direction d) const;

        /**
         * Notify all PlacedTokens, currently placed in row y, about the movement
         * @param y moved row
         * @param direction direction of movement
         */
        void notifyPlacedTokenAboutRowMovement(GameSettings::CoordType y, Geo::Direction direction);

        /**
         * Notify all PlacedTokens, currently placed in column x, about the movement
         * @param x moved column
         * @param direction direction of movement
         */
        void notifyPlacedTokenAboutColumnMovement(GameSettings::CoordType x, Geo::Direction direction);

        /**
         * Internal methode to build the MazePieces used in this game
         * @return A vector consisting of MazePieces
         */
        [[nodiscard]] std::vector<MazePiece> initiallyCreateMazePieces() const;

        /**
         * Build \a _graph according to a previously initialized \a _maze
         */
        void initiallyBuildGraphFromMaze();

        /**
         * Updates the underlying graph structure according to changes at a column x
         * @param x the column index
         */
        void updateGraphAccordingToColumnChanges(GameSettings::CoordType x);

        /**
         * Updates the underlying graph structure according to changes at a row y
         * @param y the row index
         */
        void updateGraphAccordingToRowChanges(GameSettings::CoordType y);

        /**
         * Updates the underlying graph structure according to changes at a coordinate c
         * @param c The coordinate
         */
        void updateCoordinate(Coordinate const &c);

        ////////////////
        /// Logger
        static Logger _logger;
        [[nodiscard]] static inline Logger const &LOG()
        {
            return _logger;
        }
    };

} // namespace LabyrinthGame
#endif // HACKATHON_2021_GAMEBOARD_H
