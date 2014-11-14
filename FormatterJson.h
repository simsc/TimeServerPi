#include "Formatter.h"

class FormatterJson : public Formatter
{
public:
    FormatterJson();
    ~FormatterJson();
	string format(tm*);
};

