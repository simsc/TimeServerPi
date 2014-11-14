//
//  Server.h
//  Server
//
//  Created by Simon on 30.10.14
//  Copyright (c) 2014 Simon. All rights reserved.
//

#ifndef __Server__Server__
#define __Server__Server__

#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <chrono>

class Server {
public:
    Server();
    void serve();
    void stopServing();
private:
    static void acceptConnection(int newsockfd);
    bool serving;
    void error(std::string message);
};

#endif /* defined(__Server__Server__) */
