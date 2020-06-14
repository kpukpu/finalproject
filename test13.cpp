#include "wtgraph.h"

void main()
{
	int r, c;
	cin >> r >> c;
	WtGraph<int> testGraph(r, c);
	testGraph.insertMaze();
}