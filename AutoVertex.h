#pragma once
#include "Vertex.h"
#include <string>

class AutoVertex :
	public Vertex
{
private:
	string m_kind;
	bool m_is_first;
	
public:
	AutoVertex();
	AutoVertex(string name);
	~AutoVertex();
	const string get_Kind()const;
	const bool is_first()const;
	void set_first();

};

