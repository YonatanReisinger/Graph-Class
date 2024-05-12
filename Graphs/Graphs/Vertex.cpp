#include "Graph.h"

Graph::Vertex:: Vertex(int value)
{
    this->setValue(value);
}

int Graph::Vertex::getValue() const
{
    return m_value;
}

void Graph::Vertex::setValue(int value)
{
    this->m_value = value;
}
bool Graph::Vertex:: operator ==(const Vertex& v) const
{
    return this->m_value == v.getValue();
}