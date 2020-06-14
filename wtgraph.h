//--------------------------------------------------------------------
//
//  Laboratory 13                                          wtgraph.h
//
//  Class declaration for the adjacency matrix implementation of
//  the Weighted Graph ADT
//
//--------------------------------------------------------------------

#include <climits>    // For INT_MAX
#include <new>
#include <stdexcept>
#include <string>
#include <iostream>


using namespace std;


//--------------------------------------------------------------------
template < class QE >
class wtGraph;


//--------------------------------------------------------------------
template < class QE >
class WtGraph
{
public:

	WtGraph(int r, int c)
		throw (bad_alloc);

	// Graph manipulation operations
	void insertMaze()            // Insert vertex
		throw (logic_error);
	void makeMaze()    // Insert edge
		throw (logic_error);

	void FB_BFS(int sx, int sy, int bx, int by, int gx, int gy);
	void FG_BFS(int sx, int sy, int bx, int by, int gx, int gy);

private:
	// Data members
	// Maximum number of vertices in the graph
	int **adjMatrix;       // Adjacency matrix
	int rs, cs;
	bool **visited;
};

