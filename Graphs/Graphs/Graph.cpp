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
Graph:: ~Graph()
{
    delete[] m_vertices;
    delete[] m_arrayOfadjacencyLists;
    this->m_vertices = 0;
}
Graph:: Graph(const Graph& otherGraph)
{
    this->m_numOfVertices = otherGraph.m_numOfVertices;
    this->m_arrayOfadjacencyLists = new list<Vertex>[m_numOfVertices];
    this->m_vertices = new Vertex[m_numOfVertices];
    for (int i = 0; i < m_numOfVertices; i++)
    {
        this->m_vertices[i] = otherGraph.m_vertices[i];
    }
    for (int i = 0; i < m_numOfVertices; i++)
    {
        // deep copy all the vertices from the other graph
        for (Vertex copiedVertex : otherGraph.m_arrayOfadjacencyLists[i])
        {
            this->m_arrayOfadjacencyLists[i].push_back(copiedVertex);
        }
    }
}
Graph& Graph:: operator=(const Graph& otherGraph)
{
    if (this != &otherGraph) // Check for self-assignment
    {
        delete[] m_vertices;
        delete[] m_arrayOfadjacencyLists;

        // Copy from the right-hand side object
        this->m_numOfVertices = otherGraph.m_numOfVertices;
        this->m_arrayOfadjacencyLists = new list<Vertex>[m_numOfVertices];
        this->m_vertices = new Vertex[m_numOfVertices];

        // Deep copy vertices
        for (int i = 0; i < m_numOfVertices; i++)
        {
            this->m_vertices[i] = otherGraph.m_vertices[i];
        }

        // Deep copy adjacency lists
        for (int i = 0; i < m_numOfVertices; i++)
        {
            for (const Vertex& vertex : otherGraph.m_arrayOfadjacencyLists[i])
            {
                this->m_arrayOfadjacencyLists[i].push_back(vertex);
            }
        }
    }

    return *this;
}
unsigned int Graph:: getVertexIndex(const Vertex& v) const
{
    return v.getValue() - 1;
}
bool Graph::IsAdjacent(const Vertex& u, const Vertex& v) const
{
    const list<Vertex>& uAdjacencyList = GetAdjList(u); // GetAdjList checks that u actually exists
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
list<Graph:: Vertex>& Graph::GetAdjList(const Vertex& u)
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
const list<Graph::Vertex>& Graph::GetAdjList(const Vertex& u) const
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
    list<Vertex>& uAdjacencyList = GetAdjList(u); // GetAdjList checks that u actually exists
    
    if (isVertexInGraph(u) && isVertexInGraph(v) && !IsAdjacent(u, v))
    {
        uAdjacencyList.push_back(v);
    }
    else
    {
        PrintinvalidInputMessage(); // The graph is simple, thus no double edges are allowed
    }
}
void Graph:: RemoveEdge(const Vertex& u, const Vertex& v)
{
    list<Vertex>& uAdjacencyList = GetAdjList(u); // GetAdjList checks that u actually exists
    
    if (isVertexInGraph(u) && isVertexInGraph(v) && IsAdjacent(u, v))
    {
        uAdjacencyList.remove(v);
    }
    else
    {
        PrintinvalidInputMessage(); // Try To delte a non existing edge
    }
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
ostream& operator<<(ostream& os, const Graph& graph)
{
    os << "Graph:" << endl;
    for (int i = 0; i < graph.m_numOfVertices; ++i)
    {
        const Graph:: Vertex& currentVertex = graph.m_vertices[i];
        const list<Graph:: Vertex>& adjacencyList = graph.m_arrayOfadjacencyLists[i];

        os << "Vertex " << currentVertex.getValue() << " is adjacent to: ";
        for (const Graph:: Vertex& adjacentVertex : adjacencyList)
        {
            os << adjacentVertex.getValue() << " ";
        }
        os << endl;
    }

    return os;
}
Graph Graph:: MakeEmptyGraph(int n)
{
    return Graph(n);
}
Graph  Graph:: MakeTranspose() const
{
    Graph gTranspose(m_numOfVertices);
    unsigned int indexOfVertexInTransposeGraph;

    for (int i = 0; i < m_numOfVertices; i++)
    {
        Vertex sourceVertex = m_vertices[i];
        for (Vertex destinationVertex : this->m_arrayOfadjacencyLists[i])
        {
            indexOfVertexInTransposeGraph = gTranspose.getVertexIndex(destinationVertex);
            gTranspose.m_arrayOfadjacencyLists[indexOfVertexInTransposeGraph].push_back(sourceVertex);
        }
    }

    return gTranspose;
}
unsigned int Graph:: getNumOfVertices() const
{
    return m_numOfVertices;
}
void Graph:: PrintinvalidInputMessage() const
{
    cout << "invalid input" << endl;
    exit(1);
}