#include "Graph.h"

Graph:: Graph(int numOfVertices)
{
    if (numOfVertices > 0)
    {
        this->numOfVertices = numOfVertices;
        this->adjList = new list<Vertex>[numOfVertices];
        this->vertices = new Vertex[numOfVertices];
        for (int i = 0; i < numOfVertices; i++)
        {
            vertices[i].setValue(i + 1);
        }
    }
    else
    {
        cout << "invalid input" << endl;
        exit(1);
    }
}

bool Graph::IsAdjacent(Vertex u, Vertex v)
{

}
list<Graph:: Vertex> Graph::GetAdjList(Vertex u)
{

}
void Graph::AddEdge(Vertex u, Vertex v)
{

}
bool Graph:: RemoveEdge(Vertex u, Vertex v)
{

}