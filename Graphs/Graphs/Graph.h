#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <list>
#include <iostream>
using namespace std;

class Graph
{
public:
	explicit Graph(int numOfVertices);

	class Vertex
	{
	private:
		int value;
	public:
		Vertex(int value = 0);
		int getValue();
		void setValue(int value);
	};

	bool IsAdjacent(Vertex u, Vertex v);
	list<Vertex> GetAdjList(Vertex u);
	void AddEdge(Vertex u, Vertex v);
	bool RemoveEdge(Vertex u, Vertex v);

private:
	unsigned int numOfVertices;
	Vertex* vertices;
	list<Vertex> *adjList;
protected:

};

#endif //__GRAPH_H__

