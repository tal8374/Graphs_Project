#include "OutOfMemoryException.h"


OutOfMemoryException::OutOfMemoryException()
{
}


OutOfMemoryException::~OutOfMemoryException()
{
}

void OutOfMemoryException::print_Error()
{
	cout << "Exception: Out of Memory" << endl;
}