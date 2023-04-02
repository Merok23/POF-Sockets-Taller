#include "common_socket.h"
#include "message.h"

class Client{
 //   Socket socket;

    public:

        Client(const char* ip,const char* port);      
        int readFromFile(const char* filename);
        int sendMessage(const u_int32_t message, size_t size);
        int recieveMessage(const char* buffer);
        int printStatus(const char* recievedStatus);
//        int closeConnection();

        ~Client();
};