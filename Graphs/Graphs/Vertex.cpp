#include "Graph.h"

Graph::Vertex:: Vertex(int value)
{
    this->setValue(value);
}

int Graph::Vertex::getValue() const
{
    return value;
}

void Graph::Vertex::setValue(int value)
{
    this->value = value;
}
bool Graph::Vertex:: operator ==(const Vertex& v) const
{
    return this->value == v.getValue();
}