#include "BreadthFirstSearch.h"
#include <cassert>

namespace Combinatorics
{
	BreadthFirstSearch::BreadthFirstSearch(const Graph& g_, VertexId start_id)
		:
		_g(g_),
		_predecessor(g_, Graph::INVALID_VERTEX_ID),
		_dist(g_, Graph::INVALID_VERTEX_ID)
	{
		run(start_id, [](EdgeId) {return true; });
	}

	BreadthFirstSearch::BreadthFirstSearch(const Graph& g_, std::set<EdgeId> const& forbidden_edge, VertexId start_id)
		:
		_g(g_),
		_predecessor(g_, Graph::INVALID_VERTEX_ID),
		_dist(g_, Graph::INVALID_VERTEX_ID)
	{
		run(start_id, [&forbidden_edge](EdgeId e) {return forbidden_edge.find(e) == forbidden_edge.end(); });
	}

	BreadthFirstSearch::BreadthFirstSearch(const Graph& g_, VertexId forbidden_id, VertexId const& start_id)
		:
		_g(g_),
		_predecessor(g_, Graph::INVALID_VERTEX_ID),
		_dist(g_, Graph::INVALID_VERTEX_ID)
	{
		assert(forbidden_id != start_id);
		auto forbid_edges_to_forbidden_vertex = [&g_, &forbidden_id](EdgeId e)
		{
			return !g_.getEdge(e).isAdjacent(forbidden_id);
		};
		run(start_id, forbid_edges_to_forbidden_vertex);
	}

	[[maybe_unused]] BreadthFirstSearch::BreadthFirstSearch(const Graph& g_, Vertex const& forbidden_vertex, Vertex const& start_vertex)
		:
		BreadthFirstSearch(g_, forbidden_vertex.getId(), start_vertex.getId())
	{}

	[[maybe_unused]] BreadthFirstSearch::BreadthFirstSearch(const Graph& g, Vertex const& start_vertex)
		:
		BreadthFirstSearch(g, start_vertex.getId())
	{}

	[[maybe_unused]] BreadthFirstSearch::BreadthFirstSearch(const Graph& g, std::set<EdgeId> const& forbidden_edge,
		Vertex const& start_vertex)
		:
		BreadthFirstSearch(g, forbidden_edge, start_vertex.getId())
	{}

	[[maybe_unused]] const Graph& BreadthFirstSearch::getGraph() const
	{
		return _g;
	}

	[[maybe_unused]] VertexId BreadthFirstSearch::getStartId() const
	{
		return _start_id;
	}

	[[maybe_unused]] const VertexVector<VertexId>& BreadthFirstSearch::getPredecessorVector() const
	{
		return _predecessor;
	}

	[[maybe_unused]] const VertexVector<VertexId>& BreadthFirstSearch::getDistVector() const
	{
		return _dist;
	}

	[[maybe_unused]] bool BreadthFirstSearch::isReachable(VertexId t) const
	{
		return _dist[t] != Graph::INVALID_VERTEX_ID;
	}

	[[maybe_unused]] bool BreadthFirstSearch::isReachable(Vertex const& t) const
	{
		return isReachable(t.getId());
	}

	[[maybe_unused]] std::list<VertexId> BreadthFirstSearch::getPath(VertexId t) const
	{
		if (!isReachable(t))
		{
			throw std::runtime_error("BFS: Invalid getPath command to non-reachable t");
		}

		std::list<VertexId> res;
		VertexId current = t;
		while (current != getStartId())
		{
			res.push_front(current);
			current = getPredecessor(current);
		}
		res.push_front(getStartId());
		return res;
	}

	[[maybe_unused]] std::list<VertexId> BreadthFirstSearch::getPath(Vertex const& t) const
	{
		return getPath(t.getId());
	}

	[[maybe_unused]] VertexId BreadthFirstSearch::getPredecessor(VertexId t) const
	{
		assert(t < _g.numVertices());
		return _predecessor[t];
	}

	[[maybe_unused]] VertexId BreadthFirstSearch::getPredecessor(Vertex const& t) const
	{
		return getPredecessor(t.getId());
	}

	[[maybe_unused]] VertexId BreadthFirstSearch::getDist(VertexId t) const
	{
		assert(t < _g.numVertices());
		return _dist[t];
	}

	[[maybe_unused]] VertexId BreadthFirstSearch::getDist(Vertex const& t) const
	{
		return getDist(t.getId());
	}
}


