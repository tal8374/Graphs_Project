#include "RegularEdge.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib> 

RegularEdge::RegularEdge() :Edge()
{
	m_Wieght = 0;
	m_Memory_Size = 2;
}

RegularEdge::RegularEdge(string edgeData, map<string, Vertex*>& allVertexs)
{
	if (edgeData.length() == 0 )
		throw InvalidInputException();
	m_Memory_Size = 2;
	size_t pos = 0;
	string tokens[3];
	int i = 0;
	while ((pos = edgeData.find(',')) != std::string::npos) {
		tokens[i++] = edgeData.substr(0, pos);
		if (tokens[i - 1].length() == 0)
			throw InvalidInputException();
		//cout << tokens << std::endl;
		edgeData.erase(0, pos + 1);
		if (i > 2)
		{
			throw InvalidInputException();
		}
	}
	tokens[2] = edgeData;
	m_Name = tokens[0] + tokens[1];
	setVertexFromMap(tokens[0], tokens[1], allVertexs);
	try
	{
		m_Wieght = atof(tokens[2].c_str());
		stringstream ss;
		ss << m_Wieght;
		if (ss.str() != tokens[2])
			throw InvalidInputException();
	}
	catch (...)
	{
		throw InvalidInputException();
	}

}


RegularEdge::~RegularEdge()
{
}

double RegularEdge::getWieght()const
{
	return m_Wieght * 1.0;
}

