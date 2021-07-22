#include "gtest/gtest.h"
#include "../../../Graph/Graph.h"
#include "../../../Graph/Algorithm/BreadthFirstSearch.h"

using namespace Combinatorics;

// Create testgraph (beginning with empty graph g) with 11 vertices and 12 edges
void build_testgraph_11_12(Graph& g)
{
	g.addVertices(11);
	g.addEdge(0, 2);  //0
	g.addEdge(1, 2);  //1
	g.addEdge(1, 3);  //2
	g.addEdge(1, 4);  //3
	g.addEdge(2, 3);  //4
	g.addEdge(3, 6);  //5
	g.addEdge(4, 5);  //6
	g.addEdge(5, 6);  //7
	g.addEdge(5, 7);  //8
	g.addEdge(6, 7);  //9
	g.addEdge(7, 8);  //10
	g.addEdge(9, 10); //11
}


TEST(GraphTests, CreateGraph) {

	Graph g(20);
	g.addEdge(3, 4);
	g.addEdge(3, 15);
	g.addEdge(0, 3);
	ASSERT_EQ(g.numVertices(), 20);
	ASSERT_EQ(g.numEdges(), 3);
	ASSERT_EQ(g.getVertex(3).numEdges(), 3);
	ASSERT_EQ(g.getVertex(0).numEdges(), 1);
	ASSERT_EQ(g.getVertex(1).numEdges(), 0);
}

TEST(GraphTests, hasEdge)
{
	Graph g;
	build_testgraph_11_12(g);
	ASSERT_TRUE(g.hasEdge(0, 2));
	ASSERT_TRUE(g.hasEdge(2, 0));
	ASSERT_TRUE(g.hasEdge(3, 6));
	ASSERT_TRUE(g.hasEdge(7, 6));
	ASSERT_TRUE(g.hasEdge(4, 5));
	ASSERT_TRUE(g.hasEdge(9, 10));
	for (VertexId k = 0; k < 9; ++k)
	{
		ASSERT_FALSE(g.hasEdge(k, 10));
		ASSERT_FALSE(g.hasEdge(10, k));
	}
	ASSERT_FALSE(g.hasEdge(0, 5));
	ASSERT_FALSE(g.hasEdge(5, 0));
	ASSERT_FALSE(g.hasEdge(1, 8));
	ASSERT_FALSE(g.hasEdge(2, 6));
	ASSERT_FALSE(g.hasEdge(7, 3));
}

TEST(GraphTests, findEdge)
{
	Graph g;
	build_testgraph_11_12(g);
	auto findEdgeTest = [&g](EdgeId v, EdgeId w) {return g.getEdge(g.findEdge(v, w)).connects(v, w); };
	auto findEdgeFailureTest = [&g](EdgeId v, EdgeId w) {return g.findEdge(v, w) == Graph::INVALID_EDGE_ID; };

	ASSERT_TRUE(findEdgeTest(0, 2));
	ASSERT_TRUE(findEdgeTest(2, 0));
	ASSERT_TRUE(findEdgeTest(3, 6));
	ASSERT_TRUE(findEdgeTest(7, 6));
	ASSERT_TRUE(findEdgeTest(4, 5));
	ASSERT_TRUE(findEdgeTest(9, 10));
	for (VertexId k = 0; k < 9; ++k)
	{
		ASSERT_TRUE(findEdgeFailureTest(k, 10));
		ASSERT_TRUE(findEdgeFailureTest(10, k));
	}
	ASSERT_TRUE(findEdgeFailureTest(0, 5));
	ASSERT_TRUE(findEdgeFailureTest(5, 0));
	ASSERT_TRUE(findEdgeFailureTest(1, 8));
	ASSERT_TRUE(findEdgeFailureTest(2, 6));
	ASSERT_TRUE(findEdgeFailureTest(7, 3));
}

TEST(GraphTests, removeEdge)
{
	Graph g;
	build_testgraph_11_12(g);
	ASSERT_TRUE(g.hasEdge(0, 2));
	g.removeEdge(0, 2);
	ASSERT_FALSE(g.hasEdge(2, 0));
	ASSERT_FALSE(g.hasEdge(0, 2));
	ASSERT_TRUE(g.hasEdge(3, 6));
	ASSERT_TRUE(g.hasEdge(7, 6));
	ASSERT_TRUE(g.hasEdge(4, 5));
	ASSERT_TRUE(g.hasEdge(9, 10));
	ASSERT_EQ(g.numEdges(), 11);
	ASSERT_EQ(g.getVertex(0).degree(), 0);
	ASSERT_EQ(g.getVertex(2).degree(), 2);
}

TEST(GraphTests, BFS)
{
	Graph g;
	build_testgraph_11_12(g);

	// run bfs
	BreadthFirstSearch bfs(g, 0);
	ASSERT_EQ(bfs.getStartId(), 0);

	ASSERT_EQ(bfs.getDist(0), 0);
	ASSERT_EQ(bfs.getDist(1), 2);
	ASSERT_EQ(bfs.getDist(2), 1);
	ASSERT_EQ(bfs.getDist(3), 2);
	ASSERT_EQ(bfs.getDist(4), 3);
	ASSERT_EQ(bfs.getDist(5), 4);
	ASSERT_EQ(bfs.getDist(6), 3);
	ASSERT_EQ(bfs.getDist(7), 4);
	ASSERT_EQ(bfs.getDist(8), 5);
	ASSERT_EQ(bfs.getDist(9), Graph::INVALID_VERTEX_ID);
	ASSERT_EQ(bfs.getDist(10), Graph::INVALID_VERTEX_ID);

	ASSERT_EQ(bfs.getPredecessor(0), Graph::INVALID_VERTEX_ID);
	ASSERT_EQ(bfs.getPredecessor(1), 2);
	ASSERT_EQ(bfs.getPredecessor(2), 0);
	ASSERT_EQ(bfs.getPredecessor(3), 2);
	ASSERT_EQ(bfs.getPredecessor(4), 1);
	ASSERT_TRUE(bfs.getPredecessor(5) == 4 || bfs.getPredecessor(5) == 6);
	ASSERT_EQ(bfs.getPredecessor(6), 3);
	ASSERT_EQ(bfs.getPredecessor(7), 6);
	ASSERT_EQ(bfs.getPredecessor(8), 7);
	ASSERT_EQ(bfs.getPredecessor(9), Graph::INVALID_VERTEX_ID);
	ASSERT_EQ(bfs.getPredecessor(10), Graph::INVALID_VERTEX_ID);

	ASSERT_EQ(bfs.isReachable(9), false);
	ASSERT_EQ(bfs.isReachable(3), true);
	ASSERT_EQ(bfs.isReachable(g.getVertex(2)), true);
	ASSERT_EQ(bfs.isReachable(g.getVertex(10)), false);
	ASSERT_EQ(bfs.isReachable(g.getVertex(0)), true);
}

TEST(GraphTests, BFS_forbidden_vertex)
{
	{
		Graph g;
		build_testgraph_11_12(g);

		// run bfs
		BreadthFirstSearch bfs(g, 2, 0);

		ASSERT_EQ(bfs.getStartId(), 0);

		ASSERT_EQ(bfs.getDist(0), 0);
		ASSERT_EQ(bfs.getDist(1), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getDist(2), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getDist(3), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getDist(4), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getDist(5), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getDist(6), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getDist(7), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getDist(8), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getDist(9), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getDist(10), Graph::INVALID_VERTEX_ID);

		ASSERT_EQ(bfs.getPredecessor(0), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getPredecessor(1), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getPredecessor(2), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getPredecessor(3), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getPredecessor(4), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getPredecessor(5), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getPredecessor(6), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getPredecessor(7), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getPredecessor(8), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getPredecessor(9), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getPredecessor(10), Graph::INVALID_VERTEX_ID);

		ASSERT_EQ(bfs.isReachable(9), false);
		ASSERT_EQ(bfs.isReachable(3), false);
		ASSERT_EQ(bfs.isReachable(g.getVertex(2)), false);
		ASSERT_EQ(bfs.isReachable(g.getVertex(10)), false);
		ASSERT_EQ(bfs.isReachable(g.getVertex(0)), true);
	}
	{
		Graph g;
		build_testgraph_11_12(g);

		// run bfs
		BreadthFirstSearch bfs(g, 1, 0);

		ASSERT_EQ(bfs.getStartId(), 0);

		ASSERT_EQ(bfs.getDist(0), 0);
		ASSERT_EQ(bfs.getDist(1), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getDist(2), 1);
		ASSERT_EQ(bfs.getDist(3), 2);
		ASSERT_EQ(bfs.getDist(4), 5);
		ASSERT_EQ(bfs.getDist(5), 4);
		ASSERT_EQ(bfs.getDist(6), 3);
		ASSERT_EQ(bfs.getDist(7), 4);
		ASSERT_EQ(bfs.getDist(8), 5);
		ASSERT_EQ(bfs.getDist(9), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getDist(10), Graph::INVALID_VERTEX_ID);

		ASSERT_EQ(bfs.getPredecessor(0), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getPredecessor(1), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getPredecessor(2), 0);
		ASSERT_EQ(bfs.getPredecessor(3), 2);
		ASSERT_EQ(bfs.getPredecessor(4), 5);
		ASSERT_EQ(bfs.getPredecessor(5), 6);
		ASSERT_EQ(bfs.getPredecessor(6), 3);
		ASSERT_EQ(bfs.getPredecessor(7), 6);
		ASSERT_EQ(bfs.getPredecessor(8), 7);
		ASSERT_EQ(bfs.getPredecessor(9), Graph::INVALID_VERTEX_ID);
		ASSERT_EQ(bfs.getPredecessor(10), Graph::INVALID_VERTEX_ID);

		ASSERT_EQ(bfs.isReachable(9), false);
		ASSERT_EQ(bfs.isReachable(3), true);
		ASSERT_EQ(bfs.isReachable(g.getVertex(2)), true);
		ASSERT_EQ(bfs.isReachable(g.getVertex(10)), false);
		ASSERT_EQ(bfs.isReachable(g.getVertex(0)), true);
	}
}

TEST(GraphTests, BFS_Path)
{
	Graph g;
	build_testgraph_11_12(g);

	// run bfs
	BreadthFirstSearch bfs(g, 0);

	// get paths
	std::list<VertexId> path_0_7 = bfs.getPath(7);
	std::list<VertexId> path_0_0 = bfs.getPath(0);
	std::list<VertexId> path_0_2 = bfs.getPath(2);

	ASSERT_EQ(path_0_0.size(), 1);
	ASSERT_EQ(path_0_7.size(), 5);
	ASSERT_EQ(path_0_2.size(), 2);
	ASSERT_TRUE(path_0_0.front() == 0);

	auto it = path_0_2.begin();
	ASSERT_EQ(*it, 0);
	ASSERT_EQ(*++it, 2);
	ASSERT_EQ(++it, path_0_2.end());

	it = path_0_7.begin();
	ASSERT_EQ(*it, 0);
	ASSERT_EQ(*++it, 2);
	ASSERT_EQ(*++it, 3);
	ASSERT_EQ(*++it, 6);
	ASSERT_EQ(*++it, 7);
	ASSERT_EQ(++it, path_0_7.end());
}



TEST(GraphTests, BFS_Path_throw)
{
	Graph g;
	build_testgraph_11_12(g);

	// run bfs
	BreadthFirstSearch bfs(g, 0);

	// try to get non-existing path
   // ASSERT_THROW(bfs.getPath(9), std::runtime_error);
}
