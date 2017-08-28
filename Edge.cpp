#include "Edge.h"

Edge::Edge() :m_From(NULL), m_To(NULL), m_Name("NONE") {}

Edge::Edge(string name, Vertex& from, Vertex& to) : m_From(&from), m_To(&to), m_Name(name) {}

Edge::~Edge() {}

string Edge::getName()const
{
	return m_Name;
}

void Edge::setVertexFromMap(string vertexFrom, string vertexTo, map<string, Vertex*>& allVertexs)
{
	map<string, Vertex*>::iterator element = allVertexs.find(vertexFrom);
	if (element != allVertexs.end())
	{
		m_From = (element->second);
		m_From->setOutEdge(m_Name);
	}
	else
	{
		throw UndefinedVerticeException(vertexFrom);
	}
	element = allVertexs.find(vertexTo);
	if (element != allVertexs.end())
	{
		m_To = (element->second);
	}
	else
	{
		throw UndefinedVerticeException(vertexTo);
	}
}

Vertex& Edge::getFromVertex()const
{
	return *m_From;
}

Vertex& Edge::getToVertex()const
{
	return *m_To;
}

int Edge::get_Memory_Size()
{
	return m_Memory_Size;
}


