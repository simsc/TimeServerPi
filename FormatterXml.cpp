#include "FormatterXml.h"


XmlFormatter::XmlFormatter()
{
}


XmlFormatter::~XmlFormatter()
{
}


string XmlFormatter::format(tm* nun){

	string str = "";
	str.append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	str.append("<dt_inf>");												// the Xml-file needs a root
	str.append("<date>");
	str.append("<day>" + to_string(nun->tm_mday) + "</day>");			// day
	str.append("<month>" + to_string(nun->tm_mon + 1) + "</month>");	// month
	str.append("<year>" + to_string(nun->tm_year + 1900) + "</year>");	// year
	str.append("</date>");
	str.append("<time>");
	str.append("<hour>" + to_string(nun->tm_hour) + "</hour>");			// hours
	str.append("<minute>");												// minutes

	if (nun->tm_min >= 0 && nun->tm_min <= 9){
		str.append(to_string(0));			
		str.append(to_string(nun->tm_min));			
	}
	else{ str.append(to_string(nun->tm_min)); }

	str.append("</minute>");


	str.append("<second>");												// Seconds
	if (nun->tm_sec >= 0 && nun->tm_sec <= 9){
		str.append(to_string(0));
		str.append(to_string(nun->tm_sec));
	}
	else{ str.append(to_string(nun->tm_sec)); }
	str.append("</second>");


	str.append("</time>");
	str.append("</dt_inf>");

	return str;
}
