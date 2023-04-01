#include <sys/socket.h>
#include <sys/types.h>


class Socket {
private:
    int file_descriptor;
    bool is_open;
public:
    Socket(const char* ip, int port);
    
    int sendData(const char* data, size_t size);
    
    int receiveData(char* buffer, size_t size);

    

    ~Socket();
};
