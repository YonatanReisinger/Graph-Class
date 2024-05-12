#include "Graph.h"

Graph::Vertex:: Vertex(int value)
{
    this->setValue(value);
}

int Graph::Vertex::getValue()
{
    return value;
}

void Graph::Vertex::setValue(int value)
{
    this->value = value;
}