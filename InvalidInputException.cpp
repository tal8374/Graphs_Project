#include "InvalidInputException.h"



InvalidInputException::InvalidInputException()
{
}


InvalidInputException::~InvalidInputException()
{
}

void InvalidInputException::print_Error()
{
	cout << "Exception: Invalid Input" << endl;
}
