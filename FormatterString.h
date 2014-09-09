#include "Formatter.h"

class StringFormatter : public Formatter
{
public:
	StringFormatter();
	~StringFormatter();
	string format(tm*);
};

