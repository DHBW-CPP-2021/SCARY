#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include <ostream>
#include <cassert>
#include <algorithm>

namespace Combinatorics
{
	///////
	/// Init static member
	Graph::Logger Graph::_logger;
	VertexId Graph::INVALID_VERTEX_ID = std::numeric_limits<VertexId>::max();
	EdgeId Graph::INVALID_EDGE_ID = std::numeric_limits<EdgeId>::max();


	Graph::Graph() :_vertices(), _edges()
	{}

	Graph::Graph(VertexId n) : _vertices(), _edges()
	{
		addVertices(n);
	}

	Vertex const& Graph::getVertex(VertexId id) const
	{
		assert(id < numVertices());
		return *_vertices[id];
	}

	Vertex& Graph::getVertex(VertexId id)
	{
		return const_cast<Vertex&>(static_cast<Graph const*>(this)->getVertex(id));
	}

	Edge const& Graph::getEdge(EdgeId id) const
	{
		assert(id < numEdges());
		return *_edges[id];
	}

	Edge& Graph::getEdge(EdgeId id)
	{
		return const_cast<Edge&>(static_cast<Graph const*>(this)->getEdge(id));
	}

	VertexId Graph::numVertices() const
	{
		return _vertices.size();
	}

	EdgeId Graph::numEdges() const
	{
		return _edges.size();
	}

	Vertex& Graph::addVertex()
	{
		LOG().trace("Graph: Create new vertex with id", numVertices());
		_vertices.emplace_back(std::make_unique<Vertex>(numVertices(), *this));
		return *_vertices.back();
	}

	void Graph::addVertices(Combinatorics::VertexId k)
	{
		for (VertexId i = 0; i < k; ++i)
		{
			addVertex();
		}
	}

	Edge const& Graph::addEdge(Vertex& ep1, Vertex& ep2)
	{
		LOG().trace("Graph: Create new edge between vertices", ep1, "and", ep2);
		_edges.emplace_back(std::make_unique<Edge>(numEdges(), ep1.getId(), ep2.getId(), *this));
		Edge& newEdge = *_edges.back();
		ep1.addEdge(newEdge);
		ep2.addEdge(newEdge);
		return newEdge;;
	}

	Edge const& Graph::addEdge(VertexId ep1, VertexId ep2)
	{
		return addEdge(getVertex(ep1), getVertex(ep2));
	}

	Graph::VertexConstIterator Graph::vertexBegin()  const
	{
		return VertexConstIterator(_vertices.begin());
	}

	Graph::VertexIterator Graph::vertexBegin()
	{
		return VertexIterator(_vertices.begin());
	}

	Graph::VertexIterator Graph::vertexEnd()
	{
		return VertexIterator(_vertices.end());
	}

	Graph::VertexConstIterator Graph::vertexEnd() const
	{
		return VertexConstIterator(_vertices.end());
	}

	Graph::EdgeIterator Graph::edgeBegin()
	{
		return EdgeIterator(_edges.begin());
	}

	Graph::EdgeConstIterator Graph::edgeBegin() const
	{
		return EdgeConstIterator(_edges.begin());
	}

	Graph::EdgeIterator Graph::edgeEnd()
	{
		return EdgeIterator(_edges.end());
	}

	Graph::EdgeConstIterator Graph::edgeEnd() const
	{
		return EdgeConstIterator(_edges.end());
	}

	Graph::EdgeRange Graph::edgeRange()
	{
		return EdgeRange(edgeBegin(), edgeEnd());
	}
	Graph::EdgeConstRange Graph::edgeRange() const
	{
		return EdgeConstRange(edgeBegin(), edgeEnd());
	}

	Graph::VertexRange Graph::vertexRange()
	{
		return VertexRange(vertexBegin(), vertexEnd());
	}

	Graph::VertexConstRange Graph::vertexRange() const
	{
		return VertexConstRange(vertexBegin(), vertexEnd());
	}

	void Graph::printHumanReadable() const
	{
		LOG().info("Graph contains", numVertices(), "vertices and", numEdges(), "edges");
		LOG().info("Edges:");
		for (auto& edge : edgeRange())
		{
			LOG().info(edge);
		}
	}

	bool Graph::hasEdge(VertexId v, VertexId w) const
	{
		return findEdge(v, w) != INVALID_EDGE_ID;
	}

	bool Graph::hasEdge(Vertex const& v, Vertex const& w) const
	{
		return hasEdge(v.getId(), w.getId());
	}

	void Graph::removeEdge(VertexId v, VertexId w)
	{
		EdgeId const toRemove = getVertex(v).findEdgeTo(w);
		if (toRemove == INVALID_EDGE_ID)
		{
			LOG().warning("Attempt to delete non-existing edge between", v, "and", w);
		}
		else
		{
			removeEdge(toRemove);
		}
	}

	void Graph::removeEdgeIfExistent(VertexId v, VertexId w) {
		assert(v < numVertices());
		assert(w < numVertices());
		EdgeId const toRemove = getVertex(v).findEdgeTo(w);
		if (toRemove != INVALID_EDGE_ID)
		{
			removeEdge(toRemove);
		}
	}

	void Graph::removeEdgeIfExistent(Vertex const& v, Vertex const& w) {
		removeEdgeIfExistent(v.getId(), w.getId());
	}

	void Graph::addEdgeIfNonexistent(VertexId v, VertexId w) {
		assert(v < numVertices());
		assert(w < numVertices());
		if (getVertex(v).findEdgeTo(w) == INVALID_EDGE_ID)
		{
			addEdge(v, w);
		}
	}

	void Graph::addEdgeIfNonexistent(Vertex const& v, Vertex const& w) {
		addEdgeIfNonexistent(v.getId(), w.getId());
	}


	void Graph::removeEdge(EdgeId e)
	{
		assert(e < numEdges());

		// first remove the edge from the vertices and the graph
		getVertex(getEdge(e).getEndpoint1().getId()).removeEdge(e);
		getVertex(getEdge(e).getEndpoint2().getId()).removeEdge(e);
		auto it = _edges.erase(_edges.begin() + e);

		// Now we have to shift all other edge indices down by 1. Fortunately it already refers to the element following the
		// last element
		std::for_each(
			it,
			_edges.end(),
			[](std::unique_ptr<Edge>& edge_ptr)
			{
				--edge_ptr->_id;
			});

		// Finally we have to correct the corresponding vertex edge ids
		for (Vertex& v : vertexRange())
		{
			for (EdgeId& edge_id : v._edges)
			{
				// All edge ids bigger or equal to the removed one, namely e, must be decreased
				if (edge_id >= e)
				{
					--edge_id;
				}
			}
		}
	}

	EdgeId Graph::findEdge(VertexId v, VertexId w) const
	{
		Vertex const& vertex = getVertex(v);
		return vertex.findEdgeTo(w);
	}

	EdgeId Graph::findEdge(Vertex const& v, Vertex const& w) const
	{
		return findEdge(v.getId(), w.getId());
	}

}
