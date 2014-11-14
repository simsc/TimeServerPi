//
//  Server.cpp
//  Server
//
//  Created by Simon on 30.10.14.
//  Copyright (c) 2014 Simon. All rights reserved.
//

#include "Server.h"
#include "TimeUtil.h"
#include <cstring>
#include <iostream>
#include <time.h>
#include <stdio.h>

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

    std::cout << "Start: SockId: " << newsockfd << "\n";

    // convert from buffer to string
    std::string request(buffer);

    // parse -> get time -> get response
    TimeUtil timeUtil = TimeUtil();
    std::string response = timeUtil.getRepsonse(request);

    // convert from string to c-string
    char *res = new char[response.length() + 1];
    strcpy(res, response.c_str());

    n = write(newsockfd, res, strlen(res));
    if (n < 0){
        std::cerr << "ERROR writing to socket\n";
    }
    close(newsockfd);

    std::cout << "Finished: SockId " << newsockfd << "\n";
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
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
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
