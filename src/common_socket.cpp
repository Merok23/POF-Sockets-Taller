#include socket.h

class Socket {
private:
    int file_descriptor;
    bool is_open;
public:
    Socket(const char* ip, int port);
    ~Socket();
};

Socket::Socket(/* args */){
}

Socket::~Socket(){
}