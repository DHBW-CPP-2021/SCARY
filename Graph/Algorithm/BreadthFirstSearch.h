#ifndef GAMEFIELDGRAPH_BREADTHFIRSTSEARCH_H
#define GAMEFIELDGRAPH_BREADTHFIRSTSEARCH_H

#include <set>
#include <queue>
#include <cassert>
#include <list>
#include "../Graph-commons.h"
#include "../Graph.h"
#include "../VertexVector.h"

namespace Combinatorics
{
	class BreadthFirstSearch
	{
	public:

		[[maybe_unused]] explicit BreadthFirstSearch(const Graph& g, VertexId start_id = VertexId(0));

		[[maybe_unused]] BreadthFirstSearch(const Graph& g, Vertex const& start_vertex);

		// BFS with some forbidden edges
		[[maybe_unused]] BreadthFirstSearch(const Graph& g, std::set<EdgeId> const& forbidden_edge, VertexId start_id = VertexId(0));

		// BFS with some forbidden edges
		[[maybe_unused]] [[maybe_unused]] BreadthFirstSearch(const Graph& g, std::set<EdgeId> const& forbidden_edge, Vertex const& start_vertex);

		// BFS with one forbidden vertex
		[[maybe_unused]] BreadthFirstSearch(const Graph& g, VertexId forbidden_id, VertexId const& start_id);

		// BFS with one forbidden vertex
		[[maybe_unused]] [[maybe_unused]] BreadthFirstSearch(const Graph& g, Vertex const& forbidden_vertex, Vertex const& start_vertex);

		[[maybe_unused]] [[nodiscard]] Graph const& getGraph() const;

		[[maybe_unused]] [[nodiscard]] VertexId getStartId() const;

		[[maybe_unused]] [[maybe_unused]] [[nodiscard]] const VertexVector<VertexId>& getPredecessorVector() const;

		[[maybe_unused]] [[nodiscard]] const VertexVector<VertexId>& getDistVector() const;

		[[maybe_unused]] [[nodiscard]] VertexId getPredecessor(VertexId t) const;

		[[maybe_unused]] [[nodiscard]] VertexId getDist(VertexId t) const;

		[[maybe_unused]] [[nodiscard]] VertexId getDist(Vertex const& t) const;

		[[maybe_unused]] [[nodiscard]] VertexId getPredecessor(Vertex const& t) const;

		// Get the bfs path from start_vertex to t in form of an ordered list
		[[maybe_unused]] [[nodiscard]] std::list<VertexId> getPath(VertexId t) const;

		// Get the bfs path from start_vertex to t in form of an ordered list
		[[maybe_unused]] [[nodiscard]] std::list<VertexId> getPath(Vertex const& t) const;

		// returns true if and only if t is reachable from startId
		[[maybe_unused]] [[nodiscard]] bool isReachable(VertexId t) const;
		[[maybe_unused]] [[nodiscard]] bool isReachable(Vertex const& t) const;

	private:
		Graph const& _g;

		template <typename UnaryFunction>
		void run(VertexId start_id, UnaryFunction edge_is_allowed);

		///// Result structures
		VertexId _start_id = Graph::INVALID_VERTEX_ID;
		VertexVector<VertexId> _predecessor;
		VertexVector<VertexId> _dist;
	};

	///////////////////
	/// Implementation

	template <typename UnaryFunction>
	void BreadthFirstSearch::run(VertexId start_id, UnaryFunction edge_is_allowed)
	{
		assert(static_cast<size_t>(start_id) < static_cast<size_t>(_g.numVertices()));
		_start_id = start_id;
		std::queue<VertexId> q;
		q.push(start_id);
		_dist[start_id] = 0;
		while (!q.empty())
		{
			Vertex const& current = _g.getVertex(q.front());
			q.pop();
			for (EdgeId neighbour_edge_id = EdgeId(0); neighbour_edge_id < current.numEdges(); ++neighbour_edge_id)
			{
				Edge const& edge = current.getEdge(neighbour_edge_id);
				if (edge_is_allowed(edge.getId()))
				{
					Vertex const& neighbour = edge.getOtherEndpoint(current);
					if (_dist[neighbour] == Graph::INVALID_VERTEX_ID)
					{
						// We found this vertex for the first time
						_dist[neighbour] = _dist[current] + 1;
						_predecessor[neighbour] = current.getId();
						q.push(neighbour.getId());
					}
				}
			}
		}
	}
}

#endif //GAMEFIELDGRAPH_BREADTHFIRSTSEARCH_H
