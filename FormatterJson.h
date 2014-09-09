#include "Formatter.h"

class JsonFormatter : public Formatter
{
public:
	JsonFormatter();
	~JsonFormatter();
	string format(tm*);
};

