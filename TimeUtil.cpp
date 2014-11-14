#include "TimeUtil.h"
#include "dcftime_client.h"

#include <time.h>
#include <string>
#include <iostream>
#include <stdio.h>

TimeUtil::TimeUtil() {
    m_requestObject = RequestObject();
    m_parser = Parser();
    m_formatterHtml = FormatterHtml();
    m_formatterJson = FormatterJson();
    m_formatterString = FormatterString();
    m_formatterXml = FormatterXml();
}

std::string TimeUtil::getRepsonse(std::string request) {
    std::string response = "";

    // get current date
    time_t timestamp;
    tm *now;
    timestamp = time(0); //params: 0 or the address of a time_t variable, if 0 you can init a variable
    now = localtime(&timestamp);

	// get the time from local 'server'
	dcftime_client client;
	long time = client.dcfTimeUnix();
	std::cout << "Time from Server: " << time << std::endl;
	now = localtime(&time);

    // parse request string
    int i = m_parser.parse(request, m_requestObject);

    if(i == 0) {
        response.append("HTTP/1.1 200 OK\r\nConnection: close\r\nAccess-Control-Allow-Origin: *\r\n");

        std::string acceptHeader = m_requestObject.getHeaderAccept();
        std::string resource = m_requestObject.getRessource();

        // only console output
        std::cout << "client request - accept: " << acceptHeader << std::endl;
        std::cout << "client request - resource: " << resource << std::endl;

        // first check the resource
        if(m_requestObject.getRessource() == "/dcfTime") {
            // second check the accept header
            if(m_requestObject.getHeaderAccept().substr(0, 10) == "text/plain") {
                response.append("Content-Type: text/plain\r\n\r\n");
                response.append(m_formatterString.format(now));
            } else if(m_requestObject.getHeaderAccept().substr(0, 9) == "text/html") {
                response.append("Content-Type: text/html\r\n\r\n");
                response.append(m_formatterHtml.format(now));
            } else if(m_requestObject.getHeaderAccept().substr(0, 15) == "application/xml") {
                response.append("Content-Type: application/xml\r\n\r\n");
                response.append(m_formatterXml.format(now));
            } else if(m_requestObject.getHeaderAccept().substr(0, 16) == "application/json") {
                response.append("Content-Type: application/json\r\n\r\n");
                response.append(m_formatterJson.format(now));
            }
        } else if(m_requestObject.getRessource() == "/hello") {
            response.append("Content-Type: text/html\r\n\r\n<h1>Hello, World!</h1>\n");
        } else {
            response = "HTTP/1.1 404 Not Found\r\nConnection: close\r\n\r\n<h1>Resoucrce not found</h1>";
            response.append("<p>Availible resources are <a href=\"/dcfTime\">/dcfTime</a> and <a href=\"/hello\">/hello</a></p>");
        }
    } else {
        response = "HTTP/1.1 500 Internal Server Error\r\nConnection: close\r\n\r\n<h1>Oops!</h1>";
        response.append("<p>Internal Server Error</p>");
    }
    return response;
}
