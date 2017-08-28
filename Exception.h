#pragma once
#include <iostream>

using namespace std;

class Exception
{
public:
	virtual void print_Error() = 0;
};