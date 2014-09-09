#include "Formatter.h"

class XmlFormatter : public Formatter
{
public:
	XmlFormatter();
	~XmlFormatter();
	string format(tm*);
};

