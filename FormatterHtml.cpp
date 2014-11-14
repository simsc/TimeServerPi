#include "FormatterHtml.h"
#include "FormatterString.h"


FormatterHtml::FormatterHtml()
{
}

FormatterHtml::~FormatterHtml()
{
}

string FormatterHtml::format(tm* nun){

	string str = "";
	str.append("<html><head><title>Date and Time</title></head><body><p>");
    FormatterString* s = new FormatterString();
	str.append(s->format(nun));		//day
	str.append("</p></body></html>");

	return str;
}
