#pragma once
#include "Exception.h"
class OutOfMemoryException :
	public Exception
{
public:
	OutOfMemoryException();
	~OutOfMemoryException();
	virtual void print_Error();
};

