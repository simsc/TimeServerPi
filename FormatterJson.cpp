#include "FormatterJson.h"


JsonFormatter::JsonFormatter()
{
}


JsonFormatter::~JsonFormatter()
{
}

/**
*{
"date": {
"day": "mustertag",
"month": ".... ",
"year": "...."
},

"time": {
"hour": "musterstunde",
"minute": "...."
}
}
*/
string JsonFormatter::format(tm* nun){

	string str = "";
	str.append("{\"date\": {\"day\": \"");								//{
																		//"date": {
																		//"day": "
	str.append(to_string(nun->tm_mday) + "\",  \"month\": \"");			//....", "month": "
	str.append(to_string(nun->tm_mon + 1) + "\", \"year\": \"");		//....", "year": "
	str.append(to_string(nun->tm_year + 1900) + "\"},");				//...."},
	str.append("\"time\": {\"hour\": \"");								//"time": {
																		//"hour": "
	str.append(to_string(nun->tm_hour) + "\",\"minute\": \"");			//....", "minute": "

	if (nun->tm_min >= 0 && nun->tm_min <= 9){							//min
		str.append(to_string(0));
		str.append(to_string(nun->tm_min));
	}
	else{ str.append(to_string(nun->tm_min)); }


	str.append("\",");						//...."}
																		// sec
	str.append("\"second\":\"");						//...."}

	if (nun->tm_sec >= 0 && nun->tm_sec <= 9){							//min
		str.append(to_string(0));
		str.append(to_string(nun->tm_sec));
	}
	else{ str.append(to_string(nun->tm_sec)); }
	str.append("\"}}");

	return str;
}

