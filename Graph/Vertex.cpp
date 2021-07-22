#include <algorithm>
#include <cassert>
#include <ostream>
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"

namespace Combinatorics
{
	Vertex::Vertex(VertexId id_, Graph const& graph_) :_id(id_), _graph(graph_), _edges()
	{}

	EdgeId Vertex::numEdges() const
	{
		return _edges.size();
	}

	Edge const& Vertex::getEdge(EdgeId id) const
	{
		assert(id < numEdges());
		return _graph.getEdge(_edges[id]);
	}

	VertexId Vertex::getId() const
	{
		return _id;
	}

	bool Vertex::hasEdgeTo(VertexId other) const
	{
		return findEdgeTo(other) != Graph::INVALID_EDGE_ID;
	}

	bool Vertex::hasEdgeTo(Vertex const& other) const
	{
		return findEdgeTo(other) != Graph::INVALID_EDGE_ID;
	}



	void Vertex::removeEdge(EdgeId edge)
	{
		auto toDelete = std::find_if(
			_edges.cbegin(), _edges.cend(), [edge](EdgeId current) {
				return current == edge;
			});

		if (toDelete != _edges.end()) {
			_edges.erase(toDelete);
		}
	}

	void Vertex::addEdge(Edge const& edge)
	{
		_edges.emplace_back(edge.getId());
	}

	EdgeId Vertex::findEdgeTo(VertexId other) const
	{
		VertexId const my_id = getId();
		Graph const& g = _graph;
		auto res_it = std::find_if(
			_edges.cbegin(),
			_edges.cend(),
			[my_id, other, &g](EdgeId const& id) {
				return g.getEdge(id).connects(my_id, other);
			});
		return res_it == _edges.end() ? Graph::INVALID_EDGE_ID : *res_it;
	}

	EdgeId Vertex::findEdgeTo(Vertex const& other) const
	{
		return findEdgeTo(other.getId());
	}

	EdgeId Vertex::degree() const
	{
		return _edges.size();
	}

	std::ostream& operator<<(std::ostream& out, Vertex const& v)
	{
		out << "(" << v.getId() << ")";
		return out;
	}
}
