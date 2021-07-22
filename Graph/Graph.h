#ifndef HACKATHON_GRAPH_H
#define HACKATHON_GRAPH_H

#include <memory>
#include <algorithm>
#include "Edge.h"
#include "Vertex.h"
#include "PointerIteratorWrapper.h"
#include "SimpleRange.h"
#include "../Logger/Log.h"

namespace Combinatorics
{
	class Graph
	{
		using Logger = DHBW_LOG::CoutLogger<LogLevel::DEBUG>;
	public:
		// Alias for container and iterator types
		template <typename T>
		using ContainerType = std::vector<T>;
		// use unique ptr for stable storage
		using EdgePtrContainer = ContainerType<std::unique_ptr<Edge>>;
		using EdgeIterator = PointerIteratorWrapper<Edge, EdgePtrContainer, false>;
		using EdgeConstIterator = PointerIteratorWrapper<Edge, EdgePtrContainer, true>;
		using VertexPtrContainer = ContainerType<std::unique_ptr<Vertex>>;
		using VertexIterator = PointerIteratorWrapper<Vertex, VertexPtrContainer, false>;
		using VertexConstIterator = PointerIteratorWrapper<Vertex, VertexPtrContainer, true>;
		using VertexConstRange = SimpleRange<VertexConstIterator>;
		using VertexRange = SimpleRange<VertexIterator>;
		using EdgeConstRange = SimpleRange<EdgeConstIterator>;
		using EdgeRange = SimpleRange<EdgeIterator>;

		// C'tor for empty graph
		explicit Graph();

		// C'tor for graph with n vertices
		explicit Graph(VertexId n);

		// get vertex by id
		[[nodiscard]] Vertex const& getVertex(VertexId id) const;
		[[nodiscard]] Vertex& getVertex(VertexId id);

		// get edge by id
		[[nodiscard]] Edge const& getEdge(EdgeId id) const;
		[[nodiscard]] Edge& getEdge(EdgeId id);

		// get number of vertices
		[[nodiscard]] VertexId numVertices() const;

		// get number of edges
		[[nodiscard]] EdgeId numEdges() const;

		// add a vertex and get it
		Vertex& addVertex();

		// ass k vertices
		void addVertices(VertexId k);

		// add a edge and get the id of the new edge. Parallel edges are not allowed
		Edge const& addEdge(Vertex& ep1, Vertex& ep2);

		// add a edge and get the id of the new edge. Parallel edges are not allowed
		Edge const& addEdge(VertexId ep1, VertexId ep2);

		// get iterator to the first vertex
		[[nodiscard]] VertexIterator vertexBegin();
		[[nodiscard]] VertexConstIterator vertexBegin() const;

		// get iterator to the last vertex
		[[nodiscard]] VertexIterator vertexEnd();
		[[nodiscard]] VertexConstIterator vertexEnd() const;

		// get iterator to the first edge
		[[nodiscard]] EdgeIterator edgeBegin();
		[[nodiscard]] EdgeConstIterator edgeBegin() const;

		// get iterator to the last edge
		[[nodiscard]] EdgeIterator edgeEnd();
		[[nodiscard]] EdgeConstIterator edgeEnd() const;

		// get range of edges
		[[nodiscard]] EdgeRange edgeRange();
		[[nodiscard]] EdgeConstRange edgeRange() const;

		// get range of vertices
		[[nodiscard]] VertexRange vertexRange();
		[[nodiscard]] VertexConstRange vertexRange() const;

		// prints the graph human readable on INFO level
		void printHumanReadable() const;

		// returns true if and only if there is an edge connecting v and w
		[[nodiscard]] bool hasEdge(VertexId v, VertexId w) const;

		// returns true if and only if there is an edge connecting v and w
		[[nodiscard]] bool hasEdge(Vertex const& v, Vertex const& w) const;

		// returns the EdgeId of the Edge {v,w} if it exists.
		// If no edge {v,w} exists INVALID_EDGE_ID is returned
		[[nodiscard]] EdgeId findEdge(VertexId v, VertexId w) const;

		// returns the EdgeId of the Edge {v,w} if it exists.
		// If no edge {v,w} exists INVALID_EDGE_ID is returned
		[[nodiscard]] EdgeId findEdge(Vertex const& v, Vertex const& w) const;

		/**
		 * Auxiliary methode. Removes an edge {v,w} if it exists
		 * @param v First vertex
		 * @param w Second vertex
		 */
		void removeEdgeIfExistent(VertexId v, VertexId w);

		/**
		 * Auxiliary methode. Adds an edge {v,w} if such an edge does currently not exist
		 * @param v First vertex
		 * @param w Second vertex
		 */
		void addEdgeIfNonexistent(VertexId v, VertexId w);

		/**
		 * Auxiliary methode. Removes an edge {v,w} if it exists
		 * @param v First vertex
		 * @param w Second vertex
		 */
		void removeEdgeIfExistent(Vertex const& v, Vertex const& w);

		/**
		 * Auxiliary methode. Adds an edge {v,w} if such an edge does currently not exist
		 * @param v First vertex
		 * @param w Second vertex
		 */
		void addEdgeIfNonexistent(Vertex const& v, Vertex const& w);

		// Remove edge {v,w}. This is an O(m) operation given the current graph implementation
		void removeEdge(VertexId v, VertexId w);

		// Remove edge e. This is an O(m) operation given the current graph implementation
		void removeEdge(EdgeId e);

		// Removes all edges inside an container c. Pass by copy is intended since we have to sort the container
		template <typename EdgeIdContainer>
		void removeEdges(EdgeIdContainer c);

		static VertexId INVALID_VERTEX_ID;
		static EdgeId INVALID_EDGE_ID;

	private:
		VertexPtrContainer _vertices;
		EdgePtrContainer   _edges;
		static Logger _logger;
		static inline Logger const& LOG() { return _logger; }
	};


	template<typename EdgeIdContainer>
	void Graph::removeEdges(EdgeIdContainer c)
	{
		std::sort(c.begin(), c.end(), [](EdgeId a, EdgeId b) {return a > b; });
		for (auto e : c)
		{
			removeEdge(e);
		}
	}
}

#endif //HACKATHON_GRAPH_H
