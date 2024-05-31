#include <iostream>
#include <stdlib.h>
#include "Graph.h"


int main()
{
	int n;
	list<Graph::Edge> edges;

	cin >> n;
	Graph g(n);
	edges = g.getEdgesFromUser();
	g.addEdges(edges);
	
	Graph super = g.makeSuperGraph();
	cout << endl <<super.getNumOfVertices() << " " << super.getNumOfEdges() << endl;
}