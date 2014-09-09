#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Server.h"
#include <thread>

int main(void)
{
    Server *s = new Server();
    s->serve();

    // Formatter Test
    /*time_t timestamp;
    tm *nun;
    timestamp = time(0); //params: 0 or the address of a time_t variable, if 0 you can init a variable
    nun = localtime(&timestamp);

    //test the issue
    cout << nun->tm_mday << '.' << nun->tm_mon + 1 << '.'
        << nun->tm_year + 1900 << " - " << nun->tm_hour
        << ':' << nun->tm_min << endl;

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
    f3.close();*/

    return 0;
}
