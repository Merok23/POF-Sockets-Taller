#include "common_socket.h"

class Client{
    Socket socket;

    public:

        Client(const int ip,const int port,const char* filename);
        
        int readFromFile(const char* filename);
        int sendMessage(const char* message);
        int recieveMessage(const char* buffer);
        int printStatus(const char* recievedStatus);
        int closeConnection();

        ~Client();
};