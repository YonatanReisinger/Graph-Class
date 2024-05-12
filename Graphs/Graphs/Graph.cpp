#include "Graph.h"

Graph:: Graph(int numOfVertices)
{
    if (numOfVertices > 0)
    {
        this->m_numOfVertices = numOfVertices;
        this->m_arrayOfadjacencyLists = new list<Vertex>[numOfVertices];
        this->m_vertices = new Vertex[numOfVertices];
        for (int i = 0; i < numOfVertices; i++)
        {
            m_vertices[i].setValue(i + 1);
        }
    }
    else
    {
        PrintinvalidInputMessage();
    }
}

unsigned int Graph:: getVertexIndex(const Vertex& v) const
{
    return v.getValue() - 1;
}
bool Graph::IsAdjacent(const Vertex& u, const Vertex& v) const
{

    list<Vertex> uAdjacencyList = GetAdjList(u); // GetAdjList checks that u actually exists
    bool res = false;

    for (const Vertex& vertex : uAdjacencyList)
    {
        if (vertex == v)
        {
            res = true;
            break;
        }
    }

    return res;
}
list<Graph:: Vertex> Graph::GetAdjList(const Vertex& u) const
{
    if (!isVertexInGraph(u))
    {
        PrintinvalidInputMessage();
    }
    else
    {
        return m_arrayOfadjacencyLists[getVertexIndex(u)];
    }
}
void Graph::AddEdge(const Vertex& u, const Vertex& v)
{
    list<Vertex> uAdjacencyList = GetAdjList(u); // GetAdjList checks that u actually exists
    
    if (!IsAdjacent(u, v))
    {
        uAdjacencyList.push_back(v);
    }
    else
    {
        PrintinvalidInputMessage(); // The graph is simple, thus no double edges are allowed
    }
}
bool Graph:: RemoveEdge(const Vertex& u, const Vertex& v)
{
    return false;
}
bool Graph:: isVertexInGraph(const Vertex& v) const
{
    bool res = false;
    for (int i = 0; i < m_numOfVertices; i++)
    {
        if (m_vertices[i] == v)
        {
            res = true;
            break;
        }
    }

    return res;
}
void Graph:: PrintinvalidInputMessage() const
{
    cout << "invalid input" << endl;
    exit(1);
}