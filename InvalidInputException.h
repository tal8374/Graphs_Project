#pragma once
#include "Exception.h"
class InvalidInputException :
	public Exception
{
public:
	InvalidInputException();
	~InvalidInputException();
	virtual void print_Error();
};

