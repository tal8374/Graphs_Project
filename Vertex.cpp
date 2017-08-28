#include "Vertex.h"
#include <string>

Vertex::Vertex() : m_Memory_Size(4) {}

Vertex::Vertex(string name) : m_name(name) , m_Memory_Size(4 + name.length())
{

}

Vertex::~Vertex() {}

const string Vertex::getName()const
{
	return m_name;
}

void Vertex::setOutEdge(const string& edge_name)
{
	m_outEdges.push_back(edge_name);
}

vector<string> Vertex::getOutEdges()const
{
	return m_outEdges;
}

bool Vertex::operator!=(const Vertex& other)const
{
	return m_name != other.m_name;
}



int Vertex::get_Memory_Size()
{
	return m_Memory_Size;
}

