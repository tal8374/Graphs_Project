#include "automathEdge.h"
#include <iostream>


using namespace std;

AutomathEdge::AutomathEdge() : Edge() {}

AutomathEdge::AutomathEdge(string edgeData, map<string, Vertex*>& allVertexs)
{
	m_Memory_Size = 2;
	size_t pos = 0;
	string tokens[3];
	int i = 0;
	while ((pos = edgeData.find(',')) != std::string::npos)
	{
		tokens[i++] = edgeData.substr(0, pos);
		edgeData.erase(0, pos + 1);
		if (i > 2)
			throw InvalidInputException();
	}
	tokens[2] = edgeData;
	m_Name = tokens[0] + tokens[1];
	m_edge_rule = edgeData[0];
	setVertexFromMap(tokens[0], tokens[1], allVertexs);
}

AutomathEdge::~AutomathEdge() {}


char AutomathEdge::get_edge_rule()const
{
	return m_edge_rule;
}

