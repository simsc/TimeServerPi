#include "FormatterHtml.h"
#include "FormatterString.h"


HtmlFormatter::HtmlFormatter()
{
}

HtmlFormatter::~HtmlFormatter()
{
}

string HtmlFormatter::format(tm* nun){

	string str = "";
	str.append("<html><head><title>Date and Time</title></head><body><p>");
	StringFormatter* s = new StringFormatter();
	str.append(s->format(nun));		//day
	str.append("</p></body></html>");

	return str;
}
