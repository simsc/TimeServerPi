#include "FormatterString.h"
#include <iostream>

FormatterString::FormatterString()
{
}

FormatterString::~FormatterString()
{
}

string FormatterString::format(tm* nun){

	string str = ""; 
	str.append(to_string(nun->tm_mday));		// day
	str.append(".");
	str.append(to_string(nun->tm_mon + 1));		// month
	str.append(".");
	str.append(to_string(nun->tm_year + 1900)); // year
	str.append("-");
	str.append(to_string(nun->tm_hour));		// hours
	str.append(":");

	if (nun->tm_min >= 0 && nun->tm_min <= 9){	// min
		str.append(to_string(0));
		str.append(to_string(nun->tm_min));
	}
	else{ str.append(to_string(nun->tm_min)); }

	str.append(":");

	if (nun->tm_sec >= 0 && nun->tm_sec <= 9){	// sek
		str.append(to_string(0));
		str.append(to_string(nun->tm_sec));
	}
	else{ str.append(to_string(nun->tm_sec)); }


	return str;
}
