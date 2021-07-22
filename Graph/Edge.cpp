#include <cassert>
#include <ostream>


#include "Edge.h"
#include "Graph.h"
#include "Vertex.h"

namespace Combinatorics
{
    bool Edge::isAdjacent(Vertex const &v) const
    {
        return isAdjacent(v.getId());
    }

    bool Edge::isAdjacent(VertexId v) const
    {
        return (_ep1 == v || _ep2 == v);
    }

    bool Edge::connects(Vertex const &v, Vertex const &w) const
    {
        return connects(v.getId(), w.getId());
    }

    bool Edge::connects(VertexId v, VertexId w) const
    {
        return (_ep1 == v && _ep2 == w) || (_ep2 == v && _ep1 == w);
    }

    Vertex const &Edge::getOtherEndpoint(Vertex const &v) const
    {
        assert(isAdjacent(v));
        if (getEndpoint1().getId() == v.getId())
        {
            return getEndpoint2();
        }
        else
        {
            return getEndpoint1();
        }
    }

    Vertex const &Edge::getEndpoint2() const
    {
        return _graph.getVertex(_ep2);
    }

    Vertex const &Edge::getEndpoint1() const
    {
        return _graph.getVertex(_ep1);
    }

    Edge::Edge(EdgeId id_, VertexId ep1_, VertexId ep2_, Graph const &graph_)
        : _id(id_), _ep1(ep1_), _ep2(ep2_), _graph(graph_)
    {
    }

    EdgeId Edge::getId() const
    {
        return _id;
    }

    std::ostream &operator<<(std::ostream &out, Edge const &e)
    {
        out << "Edge " << e.getId() << ": " << e.getEndpoint1() << " -- " << e.getEndpoint2();
        return out;
    }
} // namespace Combinatorics
