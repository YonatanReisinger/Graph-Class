#include <iostream>
#include <stdlib.h>
#include "Graph.h"
//using namespace std;


int main()
{
	Graph g(5), g2(5);
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

	g2 = g.MakeTranspose();
	cout << g2 << endl;

}