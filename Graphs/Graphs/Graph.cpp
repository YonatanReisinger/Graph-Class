#include "Graph.h"

Graph::Graph(int numOfVertices)
{
    if (numOfVertices < 0)
    {
        PrintinvalidInputMessage();
    }
    else
    {
        m_numOfVertices = numOfVertices;
        m_numOfEdges = 0;
        m_vertices.resize(numOfVertices);
        m_arrayOfadjacencyLists.resize(numOfVertices);
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
    m_numOfEdges = otherGraph.m_numOfEdges;
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
        m_numOfEdges = otherGraph.m_numOfEdges;
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
        exit(1);
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
        exit(1);
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
        m_numOfEdges++;
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
        m_numOfEdges--;
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
unsigned int Graph::getNumOfEdges() const
{
    return m_numOfEdges;
}
void Graph:: PrintinvalidInputMessage()
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
    vector<VERTEX_COLOR> colors ;
    colors.resize(m_numOfVertices);
    for (VERTEX_COLOR vColor : colors)
    {
        vColor = WHITE;
    }

    list<Graph::Vertex> finishingList;
    for (Vertex &v : m_vertices) {
        if (colors[getVertexIndex(v)] == WHITE) {
            visit(v, colors,finishingList);
        }
    }
    return finishingList;
}
void Graph::visit(Graph::Vertex& u, vector<VERTEX_COLOR>& colors, list<Graph::Vertex>& finishingList) {
    colors[getVertexIndex(u)] = GREY;
    list<Graph::Vertex> &currAdj = this->GetAdjList(u);
    for (Vertex &v : currAdj) {
        if (colors[getVertexIndex(v)] == WHITE) {
            colors[getVertexIndex(v)] = GREY;
            visit(m_vertices[getVertexIndex(v)], colors, finishingList);
        }
    }
    colors[getVertexIndex(u)] = BLACK;
    finishingList.push_back(u);
}
void Graph:: addVertex()
{
    m_numOfVertices++;
    Vertex newVertex(m_numOfVertices);
    m_vertices.push_back(newVertex);
    m_arrayOfadjacencyLists.resize(m_numOfVertices);
}
Graph Graph::makeSuperGraph()
{
    Graph super(0);
    vector<Graph::Vertex> roots;
    map<Graph::Vertex, int> vertexToIndInSuperGraph;
    vector<VERTEX_COLOR> colors;
    Vertex currentRoot;
    list<Graph::Vertex> finishingList;

    colors.resize(m_numOfVertices);
    roots.resize(m_numOfVertices);

    for (VERTEX_COLOR vColor : colors)
    {
        vColor = WHITE;
    }

    finishingList = this->DFS();
    std:: reverse(finishingList.begin(), finishingList.end());
    Graph gTranspose = this->MakeTranspose();

    for (Vertex& u : finishingList)
    {
        if (colors[getVertexIndex(u)] == WHITE)
        {
            currentRoot = u;
            vertexToIndInSuperGraph[currentRoot] = super.getNumOfVertices();
            super.addVertex();
            superVisit(u, currentRoot, super, vertexToIndInSuperGraph, gTranspose, colors, roots);
        }
    }

    return super;
}
void Graph::superVisit(const Vertex& u, Vertex& currentRoot, Graph& super, map<Graph::Vertex, int>& vertexToIndInSuperGraph, const Graph& gTranspose, vector<VERTEX_COLOR>& colors, vector<Graph::Vertex>& roots)
{
    unsigned int uInd = getVertexIndex(u), vInd, currentRootValueInSuperGraph, rootVIndexInSuperGraph;
    const list<Graph::Vertex>& uAdjListInGTranspose = gTranspose.GetAdjList(u);
    Vertex rootOfV, rootOfVInSuperGraph, currentRootInSuperGraph;

    roots[uInd] = currentRoot;
    colors[uInd] = GREY;
    currentRootValueInSuperGraph = super.getNumOfVertices();
    currentRootInSuperGraph.setValue(currentRootValueInSuperGraph);

    for (const Vertex& v: uAdjListInGTranspose)
    {
        vInd = getVertexIndex(v);
        if (colors[vInd] == WHITE)
        {
            superVisit(v, currentRoot, super, vertexToIndInSuperGraph, gTranspose, colors, roots);
        }
        // if the color of v is black and u and v dont habve the same root thus they are in different strong components
        else if (colors[vInd] == BLACK && roots[vInd] != currentRoot)
        {
            rootVIndexInSuperGraph = vertexToIndInSuperGraph[roots[vInd]];
            rootOfV = super.m_vertices[rootVIndexInSuperGraph];
            list<Graph::Vertex>& listOfRootVInSuperGraph = super.GetAdjList(rootOfV);
            // if the last vertex in the list of v is not a current root, thus it was not added yet
            if (listOfRootVInSuperGraph.empty() || listOfRootVInSuperGraph.back() != currentRootInSuperGraph)
            {
                super.AddEdge(rootOfV, currentRootInSuperGraph);
            }
        }
    }

    colors[uInd] = BLACK;
}

