#include "UndefinedVerticeException.h"



UndefinedVerticeException::UndefinedVerticeException(string problem) : m_problem(problem)
{
}


UndefinedVerticeException::~UndefinedVerticeException()
{
}

void UndefinedVerticeException::print_Error()
{
	cout <<" Exception: Vertice " << m_problem << " undefined "<< endl;
}
