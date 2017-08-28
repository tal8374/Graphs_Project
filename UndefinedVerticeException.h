#pragma once
#include "Exception.h"
#include "Vertex.h"

class UndefinedVerticeException :
	public Exception
{
protected:
	string m_problem;
public:
	UndefinedVerticeException(string problem);
	~UndefinedVerticeException();
	virtual void print_Error();
};

