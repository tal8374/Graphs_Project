#pragma once
#include "Edge.h"
using namespace std;

class RegularEdge : public Edge
{
protected:
	float m_Wieght;

public:
	RegularEdge();
	RegularEdge(string edgeData, map<string, Vertex*>& allVertexs);
	~RegularEdge();
	virtual double getWieght()const;
};

