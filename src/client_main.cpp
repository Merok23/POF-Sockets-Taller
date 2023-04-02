#include "client_main.h"
#include "common_socket.h"
#include <stdio.h>
#include <stdlib.h>


class Client{
    Socket socket;
    Protocol protocol;

    public:

        Client(const int ip,const int port){
            socket = Socket(ip, port);
            //si falla el socket aca iria excepcion
        }

        int
        
        int readFromFile(const char* filename){
            FILE* archivo = fopen(filename, "r");

            if (archivo == NULL){
                return -1;
            }
            char* buffer = NULL;
            size_t len = 0;

            while(getline(&buffer, &len, archivo) != -1){
                if(validLine(buffer, len)){
                    sendMessage(buffer);
                }
            }
            free(buffer);
            fclose(archivo);
            return 0;
        }


        int sendMessage(const char* message){
            size_t size;
            printf("Message: %s\n", message);

            char* byte_message = protocol.translate(message, &size);
            
            //socket.sendData(byte_message, size);
            return 0;

        }

        int recieveMessage(const char* buffer);
        int printStatus(const char* recievedStatus);
        int closeConnection();

        ~Client();
        private:
        bool validLine(const char* line,const size_t len){
            Message message(line, len);
            return message.isValid();
        }
};

int main(int argc, char* argv[]){
    if (argc != 4){
        printf("Error: invalid number of arguments");
        return -1;
    }

    char* ip = argv[1];
    int port = (int) argv[2];
    char* path = argv[3];
    int numeric_ip = transformIp(ip); //removes the "." and transforms the ip into a number

    Client client(numeric_ip, port);
    printf("My ip is: %d and my port is: %d", client.getIp(), port);
    client.readFromFile(path);
    client.closeConnection();
    return 0;
}