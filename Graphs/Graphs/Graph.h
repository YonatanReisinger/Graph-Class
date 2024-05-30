#ifndef __GRAPH_H__
#define __GRAPH_H__

#define REF
#define VAL
#define CONST

#include <list>
#include <vector>
#include <iostream>
using namespace std;

class Graph
{
public:
    enum VERTEX_COLOR{WHITE,GREY,BLACK};
    class Vertex
    {
    private:
        int m_value;
        VERTEX_COLOR color;

    public:
        Vertex(int value = 0);
        int getValue() const;
        void setValue(int value);
        bool operator==(const Vertex& v) const;
        VERTEX_COLOR getColor() const;
        void setColor(VERTEX_COLOR color);
    };
    class Edge
    {
    private:
        Vertex from;
        Vertex to;

    public:
        Edge(Vertex f, Vertex t);
        Vertex getFromVertex();
        Vertex getToVertex();
    };
    explicit Graph(int numOfVertices);
    ~Graph();
    Graph(const Graph& otherGraph);
    Graph& operator=(const Graph& otherGraph);



    bool IsAdjacent(const Vertex& u, const Vertex& v) const;
    list<Vertex>& GetAdjList(const Vertex& u);
    const list<Vertex>& GetAdjList(const Vertex& u) const;
    void AddEdge(const Vertex& u, const Vertex& v);
    void RemoveEdge(const Vertex& u, const Vertex& v);
    friend ostream& operator<<(ostream& os, const Graph& graph);
    static Graph MakeEmptyGraph(int n);
    Graph MakeTranspose() const;
    void transpose();
    unsigned int getNumOfVertices() const;
    static list<Edge> getEdgesFromUser();
    void addEdges(list<Graph::Edge> edges);
    list<Graph::Vertex> DFS();
    void visit(Graph::Vertex& u, list<Graph::Vertex>& finishingList);

private:
    unsigned int m_numOfVertices;
    vector<Vertex> m_vertices;
    vector<list<Vertex>> m_arrayOfadjacencyLists;

    bool isVertexInGraph(const Vertex& v) const;
    unsigned int getVertexIndex(const Vertex& v) const;
    void PrintinvalidInputMessage() const;
};


#endif //__GRAPH_H__

