#include "Formatter.h"

class FormatterXml : public Formatter
{
public:
    FormatterXml();
    ~FormatterXml();
	string format(tm*);
};

