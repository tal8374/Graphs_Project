#include "AutoVertex.h"

AutoVertex::AutoVertex() :m_is_first(false)
{}

AutoVertex::AutoVertex(string name):m_is_first(false)
{	
	size_t pos = 0;
	pos = name.find(',');
	m_name = name.substr(0, pos);
	name.erase(0, pos + 1);
	m_kind = name;
	m_Memory_Size = 4 + m_name.length();
}


AutoVertex::~AutoVertex()
{	
}

const bool AutoVertex::is_first()const
{
	return m_is_first;
}

void AutoVertex::set_first()
{
	m_is_first = true;
}

const string AutoVertex::get_Kind()const
{
	return m_kind;
}

