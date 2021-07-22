#ifndef HACKATHON_VERTEX_H
#define HACKATHON_VERTEX_H

#include "Graph-commons.h"
#include <ostream>
#include <vector>


namespace Combinatorics
{
    /**
     * \class Vertex
     * Represents an vertex inside a graph. It is definied by
     *  - id
     *  - list of adijazent edges
     *  - reference to corresponding graph.
     */
    class Vertex
    {
        friend class Combinatorics::Graph;

    public:
        // Construct vertex without any adjazent edges
        explicit Vertex(VertexId id_, Graph const &graph);

        // Returns the number of Vertex edges i.e. the number of neighbour cities
        [[nodiscard]] EdgeId numEdges() const;

        // Return  edge
        [[nodiscard]] Edge const &getEdge(EdgeId id) const;

        // Getter for id
        [[nodiscard]] VertexId getId() const;

        // Returns an edge connecting this vertex with other. Returns Graph::INVALID_EDGE_ID if no such edge exist
        [[nodiscard]] EdgeId findEdgeTo(VertexId other) const;

        // Returns an edge connecting this vertex with other. Returns Graph::INVALID_EDGE_ID if no such edge exist
        [[nodiscard]] EdgeId findEdgeTo(Vertex const &other) const;

        // Returns true if and only if there is an edge connecting this with other.
        [[nodiscard]] bool hasEdgeTo(VertexId other) const;

        // Returns true if and only if there is an edge connecting this with other.
        [[nodiscard]] bool hasEdgeTo(Vertex const &other) const;

        // Returns the degree of this vertex, i.e. the number of adjiazent edges
        [[nodiscard]] EdgeId degree() const;

    private:
        // Add new edge
        void addEdge(Edge const &edge);

        // Remove edge
        void removeEdge(EdgeId edge);

        VertexId const _id;
        Graph const &_graph;
        std::vector<EdgeId> _edges;
    };
    // overload print methode
    std::ostream &operator<<(std::ostream &out, Vertex const &v);
} // namespace Combinatorics

#endif // HACKATHON_VERTEX_H
