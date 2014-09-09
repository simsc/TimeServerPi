#include "Formatter.h"

class HtmlFormatter : public Formatter
{
public:
	HtmlFormatter();
	~HtmlFormatter();
	string format(tm*);
};

