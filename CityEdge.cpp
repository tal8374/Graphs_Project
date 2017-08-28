#include "CityEdge.h"
#include <sstream>
#include <iostream>

using namespace std;

CityEdge::CityEdge() { m_Memory_Size = 6; }

CityEdge::~CityEdge() {}

CityEdge::CityEdge(string edgeData, map<string, Vertex*>& allVertexs)
{
	if (edgeData.length() == 0)
		throw InvalidInputException();
	m_Memory_Size = 6;
	size_t pos = 0;
	string tokens[5];
	int i = 0;
	while ((pos = edgeData.find(',')) != std::string::npos) {
		tokens[i++] = edgeData.substr(0, pos);
		if (tokens[i - 1].length() == 0)
			throw InvalidInputException();
		edgeData.erase(0, pos + 1);
		if (i > 4)
		{
			throw InvalidInputException();
		}
	}
	tokens[4] = edgeData;
	m_Name = tokens[0] + tokens[1];
	setVertexFromMap(tokens[0], tokens[1], allVertexs);
	try
	{
		stringstream ss;
		m_Roadlength = atof(tokens[2].c_str());
		m_RoadType = atof(tokens[3].c_str());
		if (m_RoadType == 0)
			throw InvalidInputException();
		m_RoadIncline = atof(tokens[4].c_str());
		ss << m_Roadlength << m_RoadType << m_RoadIncline;
		if (ss.str() != tokens[2] + tokens[3] + tokens[4])
			throw InvalidInputException();
	}
	catch (...)
	{
		throw InvalidInputException();
	}
}

double CityEdge::getWieght()const
{
	return (m_Roadlength + m_Roadlength/ m_RoadType + m_RoadIncline*m_Roadlength);
}

string CityEdge::get_Edge_Data()
{
	stringstream ss;
	ss << m_Roadlength << "-" << m_RoadType;
	return ss.str();
}
