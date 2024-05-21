#ifndef __GRAPH_H__
#define __GRAPH_H__

#define REF
#define VAL

#include <list>
#include <iostream>
using namespace std;

class Graph
{
public:
	explicit Graph(int numOfVertices);
	~Graph();
	Graph(const Graph& otherGraph);
	Graph& operator=(const Graph& otherGraph);

	class Vertex
	{
	private:
		int m_value;
	public:
		Vertex(int value = 0);
		int getValue() const;
		void setValue(int value);
		bool operator ==(const Vertex& v) const;
	};

	bool IsAdjacent(const Vertex& u, const Vertex& v) const;
	list<Vertex>& GetAdjList(const Vertex& u);
	const list<Vertex>& GetAdjList(const Vertex& u) const;
	void AddEdge(const Vertex& u, const Vertex& v);
	void RemoveEdge(const Vertex& u, const Vertex& v);
	friend ostream& operator<<(ostream& os, const Graph& graph);
	static Graph MakeEmptyGraph(int n);
	Graph MakeTranspose() const;
	unsigned int getNumOfVertices() const;
private:
	unsigned int m_numOfVertices;
	Vertex* m_vertices;
	list<Vertex> *m_arrayOfadjacencyLists;

	bool isVertexInGraph(const Vertex& v) const;
	unsigned int getVertexIndex(const Vertex& v) const;
	void PrintinvalidInputMessage() const;
protected:

};

#endif //__GRAPH_H__

