#include "Formatter.h"

class FormatterString : public Formatter
{
public:
    FormatterString();
    ~FormatterString();
	string format(tm*);
};

