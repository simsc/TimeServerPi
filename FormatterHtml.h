#include "Formatter.h"

class FormatterHtml : public Formatter
{
public:
    FormatterHtml();
    ~FormatterHtml();
	string format(tm*);
};

