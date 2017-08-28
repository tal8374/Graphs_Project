#pragma once
#include <string>
#include <vector>

using namespace std;
class Vertex
{
protected:
	string m_name;
	vector<string> m_outEdges;
	int m_Memory_Size;

public:
	Vertex();
	Vertex(string name);
	virtual ~Vertex();
	const string getName()const;
	void setOutEdge(const string& edge_name);
	vector<string> getOutEdges()const;	
	bool operator!=(const Vertex& other)const;	
	virtual int get_Memory_Size();
};

