#pragma once
#include "Edge.h"
class CityEdge :
	public Edge
{
protected:
	float m_Roadlength;
	float m_RoadIncline;
	int m_RoadType;
public:
	CityEdge();
	CityEdge(string edgeData, map<string, Vertex*>& allVertexs);
	~CityEdge();
	virtual double getWieght()const;
	virtual string get_Edge_Data();
};

