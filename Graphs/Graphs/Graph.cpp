#include "Graph.h"

Graph::Graph(int numOfVertices) : m_numOfVertices(numOfVertices), m_vertices(numOfVertices), m_arrayOfadjacencyLists(numOfVertices)
{
    if (numOfVertices <= 0)
    {
        PrintinvalidInputMessage();
    }
    else
    {
        for (int i = 0; i < numOfVertices; i++)
        {
            m_vertices[i].setValue(i + 1);
        }
    }
}
Graph:: ~Graph()
{
    // Clean up vertices
    m_vertices.clear();

    // Clean up adjacency lists
    for (auto& adjList : m_arrayOfadjacencyLists)
    {
        adjList.clear();
    }
    m_arrayOfadjacencyLists.clear();
}
Graph::Graph(const Graph& otherGraph) : m_numOfVertices(otherGraph.m_numOfVertices)
{
    // Deep copy vertices
    m_vertices.reserve(otherGraph.m_vertices.size());
    for (const Vertex& vertex : otherGraph.m_vertices)
    {
        m_vertices.emplace_back(vertex.getValue());
    }

    // Deep copy adjacency lists
    m_arrayOfadjacencyLists.reserve(otherGraph.m_arrayOfadjacencyLists.size());
    for (const auto& adjList : otherGraph.m_arrayOfadjacencyLists)
    {
        list<Vertex> newList;
        for (const Vertex& vertex : adjList)
        {
            newList.push_back(Vertex(vertex.getValue()));
        }
        m_arrayOfadjacencyLists.push_back(newList);
    }
}
Graph& Graph::operator=(const Graph& otherGraph) {
    if (this != &otherGraph)
    {
        // Deep copy vertices
        m_numOfVertices = otherGraph.m_numOfVertices;
        m_vertices.resize(m_numOfVertices);
        copy(otherGraph.m_vertices.begin(), otherGraph.m_vertices.end(), m_vertices.begin());

        // Deep copy adjacency lists
        m_arrayOfadjacencyLists.resize(m_numOfVertices);
        for (size_t i = 0; i < m_numOfVertices; ++i)
        {
            m_arrayOfadjacencyLists[i].assign(otherGraph.m_arrayOfadjacencyLists[i].begin(), otherGraph.m_arrayOfadjacencyLists[i].end());
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
    const list<Vertex>& uAdjacencyList = GetAdjList(CONST REF u); // GetAdjList checks that u actually exists
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
    if (!isVertexInGraph(CONST REF u))
    {
        PrintinvalidInputMessage();
    }
    else
    {
        return m_arrayOfadjacencyLists[getVertexIndex(CONST REF u)];
    }
}
const list<Graph::Vertex>& Graph::GetAdjList(const Vertex& u) const
{
    if (!isVertexInGraph(CONST REF u))
    {
        PrintinvalidInputMessage();
    }
    else
    {
        return m_arrayOfadjacencyLists[getVertexIndex(CONST REF u)];
    }
}
void Graph::AddEdge(const Vertex& u, const Vertex& v)
{
    list<Vertex>& uAdjacencyList = GetAdjList(CONST REF u); // GetAdjList checks that u actually exists
    
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
    list<Vertex>& uAdjacencyList = GetAdjList(CONST REF u); // GetAdjList checks that u actually exists
    
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
            indexOfVertexInTransposeGraph = gTranspose.getVertexIndex(CONST REF destinationVertex);
            gTranspose.m_arrayOfadjacencyLists[indexOfVertexInTransposeGraph].push_back(CONST REF sourceVertex);
        }
    }

    return gTranspose;
}
void Graph::transpose()
{
    *this = this->MakeTranspose();
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

list<Graph::Edge> Graph:: getEdgesFromUser() {
    cout << "Enter the number of edges:" << endl;
    int numberOfEdges;
    cin >> numberOfEdges;
    int t1, t2;
    list<Graph::Edge> edges;
    cout << "enter all edges:" << endl;
    for (int i = 0; i < numberOfEdges; ++i) {
        std::cin >> t1 >> t2;
        Vertex v1(t1);
        Vertex v2(t2);
        Edge edge(v1, v2);
        edges.push_back(edge);
    }
    return edges;
}
void Graph::addEdges(list<Graph::Edge> edgesList) {
    int n = this->getNumOfVertices();
    for (Edge e : edgesList) {
        this->AddEdge(e.getFromVertex(), e.getToVertex());
    }
 }
Graph::Vertex Graph::Edge::getFromVertex() 
{
    return this->from;
}
Graph::Vertex Graph::Edge::getToVertex()
{
    return this->to;
}
Graph::Edge::Edge(Vertex f, Vertex t)
{
    this->from = f;
    this->to = t;
}
list<Graph::Vertex> Graph::DFS() {
    list<Graph::Vertex> finishingList;
    for (Vertex &v : m_vertices) {
        if (v.getColor() == WHITE) {
            visit(v,finishingList);
        }
    }
    return finishingList;
}
void Graph::Vertex::setColor(VERTEX_COLOR color) {
    this->color = color;
}
void Graph::visit(Graph::Vertex& u,list<Graph::Vertex>& finishingList) {
    u.setColor(GREY);
    list<Graph::Vertex> &currAdj = this->GetAdjList(u);
    for (Vertex &v : currAdj) {
        if (m_vertices[v.getValue()-1].getColor() == WHITE) {
            m_vertices[v.getValue()-1].setColor(GREY);
            visit(m_vertices[v.getValue()-1], finishingList);
        }
    }
    u.setColor(BLACK);
    finishingList.push_back(u);
}