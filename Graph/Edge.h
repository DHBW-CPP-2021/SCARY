#ifndef HACKATHON_EDGE_H
#define HACKATHON_EDGE_H

#include "Graph-commons.h"

namespace Combinatorics
{
    /**
     * \class Edge
     * Represents an edge between two vertices
     */
    class Edge
    {
        friend class Combinatorics::Graph;

    public:
        // C'tor
        explicit Edge(EdgeId id_, VertexId ep1_, VertexId ep2_, Graph const &graph_);

        [[nodiscard]] Vertex const &getEndpoint1() const;
        [[nodiscard]] Vertex const &getEndpoint2() const;

        // returns the endpoint which is not v
        [[nodiscard]] Vertex const &getOtherEndpoint(Vertex const &v) const;

        // checks whether this edge is adjazant with v
        [[nodiscard]] bool isAdjacent(Vertex const &v) const;

        // checks whether this edge is adjazant with v
        [[nodiscard]] bool isAdjacent(VertexId v) const;

        // Checks whether this edge connects v and w
        [[nodiscard]] bool connects(Vertex const &v, Vertex const &w) const;

        // Checks whether this edge connects v and w
        [[nodiscard]] bool connects(VertexId v, VertexId w) const;

        // get id of edge
        [[nodiscard]] EdgeId getId() const;

    private:
        EdgeId _id;
        VertexId const _ep1;
        VertexId const _ep2;
        Graph const &_graph;
    };
    // overload print
    std::ostream &operator<<(std::ostream &out, Edge const &e);
} // namespace Combinatorics
#endif // HACKATHON_EDGE_H
