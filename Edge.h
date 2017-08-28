#pragma once
#include "Vertex.h"
#include "AutoVertex.h"
#include <string>
#include <map>
#include "Exception.h"
#include "InvalidInputException.h"
#include "OutOfMemoryException.h"
#include "UndefinedVerticeException.h"
#include <cstdlib> 

using namespace std;

class Edge
{
protected:
	string m_Name;
	Vertex *m_From, *m_To;
	void setVertexFromMap(string vertexFrom, string vertexTo, map<string, Vertex*>& allVertexs);
	int m_Memory_Size;

public:
	Edge();
	Edge(string name, Vertex& from, Vertex& to);
	virtual ~Edge();
	string getName()const;
	Vertex& getFromVertex()const;
	Vertex& getToVertex()const;
	virtual string get_Edge_Data() { return ""; };
	virtual int get_Memory_Size() ;	
	virtual double getWieght()const=0;
};

