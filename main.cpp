#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <time.h>
#include <fstream>

#include "HtmlFormatter.h"
#include "JsonFormatter.h"
#include "StringFormatter.h"
#include "XmlFormatter.h"
using namespace std;

/*
* appearance of the struct:
*
* struct tm {
*	int tm_sec;    //Sekunden
*	int tm_min;    //Minuten
*	int tm_hour;   //Stunde (0 bis 23)
*	int tm_mday;   //Tag im Monat (1 bis 31)
*	int tm_mon;    //Monat (0 bis 11)
*	int tm_year;   //Jahr (Kalenderjahr minus 1900)
*	int tm_wday;   //Wochentag (0 bis 6, Sonntag = 0)
*	int tm_yday;   //Tag im Jahr (0 bis 365)
*	int tm_isdst;  //Ungleich null bei US-Sommerzeitkonvertierung
* };
*/
int main(void)
{
	time_t timestamp;
	tm *nun;
	timestamp = time(0); //params: 0 or the address of a time_t variable, if 0 you can init a variable
	nun = localtime(&timestamp);
	
	//test the issue
	cout << "Struct selbst: " << nun->tm_mday << '.' << nun->tm_mon + 1 << '.'
		<< nun->tm_year + 1900 << " - " << nun->tm_hour
		<< ':' << nun->tm_min << ':' << nun->tm_sec << endl;

	//create testobjects
	HtmlFormatter* htmlF = new HtmlFormatter();
	JsonFormatter* jsonF = new JsonFormatter();
	StringFormatter* strF = new StringFormatter();
	XmlFormatter* xmlF = new XmlFormatter();

	cout << "\n\nhtml: \n" << htmlF->format(nun) << endl;
	cout << "\n\njson: \n" << jsonF->format(nun) << endl;
	cout << "\n\nstring: \n" << strF->format(nun) << endl;
	cout << "\n\nxml: \n" << xmlF->format(nun) << endl;

	//test the html file
	fstream f0;
	f0.open("test.html", ios::out);
	f0 << htmlF->format(nun) << endl;
	f0.close();

	//test the json file
	fstream f1;
	f1.open("test.json", ios::out);
	f1 << jsonF->format(nun) << endl;
	f1.close();

	//test the string file
	fstream f2;
	f2.open("test.string", ios::out);
	f2 << strF->format(nun) << endl;
	f2.close();

	//test the xml file
	fstream f3;
	f3.open("test.xml", ios::out);
	f3 << xmlF->format(nun) << endl;
	f3.close();

	return 0;
}