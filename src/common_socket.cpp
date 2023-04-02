#include "common_socket.h"

//Socket is heavily based on the class given material, if I had more time, it would be more original

// if it has 2 parameters it will create a socket and try to connect to the ip and port given

Socket::Socket(const char* ip, const char* port){
    Resolver resolver(ip, port, false); //false because it is not passive, its trying to connect to the server.
    int error = -1;
    int fd = -1;
    this->connected = false;
    
    while(resolver.hasNext() && !this->connected){
        struct addrinfo* address = resolver.next();
        fd = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
        if(fd == -1) continue;

        error = connect(fd, address->ai_addr, address->ai_addrlen);
        if(error == -1){
            close(fd);
            continue;
        }
    }
    this->connected = true;
    this->file_descriptor = fd;
}
// if it only has a port it will create a socket and try to listen to the port given
Socket::Socket(const char* port){
    Resolver resolver(nullptr, port, true); //true because it is passive, its waiting for a connection
    int error = -1;
    int fd = -1;
    this->connected = false;
    while(resolver.hasNext()){
        struct addrinfo *address = resolver.next();
        fd = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
        if(fd == -1) continue;

        //If I'm here it's because the socket was created successfully
        error = bind(fd, address->ai_addr, address->ai_addrlen);
        if(error == -1){
            close(fd);
            continue;
        }
        error = listen(fd, 10); //10 is the maximum number of connections that can be waiting to be accepted
        if(error == -1){
            close(fd);
            continue;
        }
    }
    //If I'm here it's because the socket was created successfully and it's listening
    this->connected = true;
    this->file_descriptor = fd;
    return;
}

int Socket::sendData(const char* data, size_t size){
    size_t size_sent = 0;
    while(size_sent < size){
        int sent = send(this->file_descriptor, data + size_sent, size - size_sent, 0);
        if(sent == -1){
            return -1; //exceptions missing
        }
        size_sent += sent;
    }
    return 0;
}

int Socket::receiveData(char* buffer, size_t size){
    size_t size_received = 0;
    while(size_received < size){
        int received = recv(this->file_descriptor, buffer + size_received, size - size_received, 0);
        if(received == -1){
            return -1; //exceptions missing
        }
        size_received += received;
    }
    return 0;
}

int Socket::disconnect(){
    if(this->connected){
        int error = shutdown(this->file_descriptor, SHUT_RDWR);
        if(error == -1){
            return -1; //exceptions missing
        }
        close(this->file_descriptor);
        this->connected = false;
    }
    return 0;
}

Socket::~Socket(){
    if(this->connected){
        Socket::disconnect();
    }
}
/* Esto es algo que estaba tratanod de hacer pero no me funciono


    int Socket::connect(const char* ip, const int port){
        if(!this->connected){
            struct sockaddr_in server_address;
            server_address.sin_family = AF_INET;
            server_address.sin_port = htons(port);
            server_address.sin_addr.s_addr = inet_addr(ip);
            
            struct in_adrr ip_numeric;
            if(inet_aton(ip, &ip_numeric) == 0){
                //throw exception
            }

            int error = connect(this->file_descriptor, (struct sockaddr*) &server_address, sizeof(server_address));

            if(error == -1){
                return -1; //exceptions missing
            }
            this->connected = true;
        }
        return 0;
    }
*/