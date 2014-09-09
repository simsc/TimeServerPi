//
//  Server.cpp
//  Server
//
//  Created by Simon on 30.10.14.
//  Copyright (c) 2014 Simon. All rights reserved.
//

#include "Server.h"
#include "Parser.h"
#include "RequestObject.h"
#include "FormatterHtml.h"
#include "FormatterJson.h"
#include "FormatterString.h"
#include "FormatterXml.h"
#include <cstring>
#include <iostream>
#include <time.h>

Server::Server()
{

}

void Server::acceptConnection(int newsockfd)
{
    long n;
    char buffer[512];
    bzero(buffer, 512);
    // read request from socket
    n = read(newsockfd, buffer, 511);

    if (n < 0) {
        std::cerr << "ERROR reading from socket\n";
    }

    std::cout << "start: sockId: " << newsockfd << "\n";

    /*******************************
     *  handle request - ergänzung *
     ******************************/
    std::string request(buffer);
    std::string response = "";

    time_t timestamp;
    tm *nun;
    timestamp = time(0); //params: 0 or the address of a time_t variable, if 0 you can init a variable
    nun = localtime(&timestamp); //HIER AUF DEN SERVER ZUGREIFEN!!!!

    HtmlFormatter* htmlF = new HtmlFormatter();
    JsonFormatter* jsonF = new JsonFormatter();
    StringFormatter* strF = new StringFormatter();
    XmlFormatter* xmlF = new XmlFormatter();

    Parser parser = Parser();
    RequestObject requestObject = RequestObject();
    int i = parser.parse(request, requestObject);

    if(i == 0) {
//        std::cout << "Output (Request Object): " << std::endl << std::endl;
//        std::cout << "HTTP Request Method: " << requestObject.getHttpRequestMethod() << std::endl;
//        std::cout << "Ressource: " << requestObject.getRessource() << std::endl;
//        std::cout << "Content Type: " << requestObject.getHeaderContentType() << std::endl;
//        std::cout << "Accept: " << requestObject.getHeaderAccept() << std::endl;
//        std::cout << "Timezone: " << requestObject.getHeaderTimezone() << std::endl;
//        std::cout << "Body: " << requestObject.getBody() << std::endl;

        if(requestObject.getRessource() == "/dcfTime") {
            if(requestObject.getHeaderAccept().substr(0, 10) == "text/plain") {
                response = "HTTP/1.1 200 OK\r\n"
                    "Connection: close\r\n"
                    "Content-Type: text/plain\r\n"
                    "Access-Control-Allow-Origin: *\r\n"
                    "\r\n";
                response.append(strF->format(nun));
            }
            if(requestObject.getHeaderAccept().substr(0, 9) == "text/html") {
                response = "HTTP/1.1 200 OK\r\n"
                    "Connection: close\r\n"
                    "Content-Type: text/html\r\n"
                    "Access-Control-Allow-Origin: *\r\n"
                    "\r\n";
                response.append(htmlF->format(nun));
            }
            if(requestObject.getHeaderAccept().substr(0, 15) == "application/xml") {
                response = "HTTP/1.1 200 OK\r\n"
                    "Connection: close\r\n"
                    "Content-Type: application/xml\r\n"
                    "Access-Control-Allow-Origin: *\r\n"
                    "\r\n";
                response.append(xmlF->format(nun));
            }
            if(requestObject.getHeaderAccept().substr(0, 16) == "application/json") {
                response = "HTTP/1.1 200 OK\r\n"
                    "Connection: close\r\n"
                    "Content-Type: application/json\r\n"
                    "Access-Control-Allow-Origin: *\r\n"
                    "\r\n";
                response.append(jsonF->format(nun));
            }
        }
        if(requestObject.getRessource() == "/hello") {
                response = "HTTP/1.1 200 OK\r\n"
                    "Connection: close\r\n"
                    "Content-Type: text/html\r\n"
                    "\r\n"
                    "<h1>Hello, World!</h1>\n";
        }
    }

    // convert from string to c-string
    char *res = new char[response.length() + 1];
    strcpy(res, response.c_str());

    /************************************
     *  handle request - ergänzung ende *
     ***********************************/

    n = write(newsockfd, res, strlen(res));
    if (n < 0){
        std::cerr << "ERROR writing to socket\n";
    }
    close(newsockfd);
    
    std::cout << "finished: sockId " << newsockfd << "\n";
}


void Server::serve()
{
    serving = true;
    int sockfd, portno = 80;
    socklen_t clilen;
    
    // sockaddr_in is defined in in.h, contains internet address
    struct sockaddr_in serv_addr, cli_addr;
    
    // AF_INET : internet version 4 protocol
    // SOCK_STREAM : reliable two-way connection
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    
    // bzero: write zeros to a byte string
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;	// allows to receive from any interface
    serv_addr.sin_port = htons(portno);		// host to network byteorder short
    
    // bind assigns address to socket
    if (::bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding");
    
    // wait for incoming connections
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    
    while(serving){
        int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");
        std::thread acceptThread(std::bind(acceptConnection, newsockfd));
        
        // give the thread it's own life
        acceptThread.detach();

    }
    close(sockfd);
    std::cout << "closed port 80\n";

}



void Server::stopServing()
{
    serving = false;
}

void Server::error(std::string message)
{
    std::cerr << message << std::endl;
}
