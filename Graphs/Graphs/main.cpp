#include <iostream>
#include <stdlib.h>
#include "Graph.h"


int main()
{
	/*Graph g(5), g2(5);
	Graph::Vertex v1(1);
	Graph::Vertex v2(2);
	Graph:: Vertex v3(3);
	Graph::Vertex v4(4);
	Graph::Vertex v5(5);

	g.AddEdge(v2, v3);
	g.AddEdge(v2, v4);
	g.AddEdge(v1, v2);
	g.AddEdge(v4, v3);
	g.AddEdge(v3, v5);

	g.transpose();*/


	/*cout << g << endl;*/
	cout << "Enter number of vertixes:" << endl;
	int n;
	cin >> n;
	Graph g(n);
	list<Graph::Edge> edges = g.getEdgesFromUser();
	g.addEdges(edges);
	list<Graph::Vertex> finishList;
	finishList = g.DFS();
	for (Graph::Vertex v : finishList)
	{
		cout << v.getValue() << "-->";
	}
	cout << endl;
}