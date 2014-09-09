#pragma once
#include <string>
#include <time.h>
using namespace std;

class Formatter
{
public:
	virtual string format(tm*) = 0;
};

