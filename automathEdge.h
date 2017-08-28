#pragma once
#include "Edge.h"
class AutomathEdge :
	public Edge
{
private:
	char m_edge_rule;
	double getWieght()const { return 0.0; };

public:
	AutomathEdge();
	AutomathEdge(string edgeData, map<string, Vertex*>& allVertexs);
	~AutomathEdge();
	char get_edge_rule()const;
	
};

