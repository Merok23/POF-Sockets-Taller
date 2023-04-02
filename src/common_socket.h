#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <iostream>

#include "common_resolver.h"


class Socket {
private:
    int file_descriptor;//this is the file descriptor of the socket
    bool connected;//this is a flag that indicates if the socket is open or not (if it is connected or not)(open is connected)

public:
    Socket();
    
    Socket(const char* ip, const char* port);//for connecting

    Socket(const char* port);//for listening
    
    int sendData(const char* data, size_t size);
    
    int receiveData(char* buffer, size_t size);

    int disconnect();

    ~Socket();
};

#endif