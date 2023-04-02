#include "client_main.h"
#include "common_socket.h"
#include <stdio.h>
#include <stdlib.h>


Client::Client(const char* ip,const char* port){
    //socket = Socket(ip, port);
    //si falla el socket aca iria excepcion
    return;
}

int Client::readFromFile(const char* filename){
    FILE* archivo = fopen(filename, "r");
    if (archivo == NULL){
        return -1;
    }
    char* buffer = NULL;
    size_t len = 0;

    while(getline(&buffer, &len, archivo) != -1){
        if(strlen(buffer) == 1) continue;
        Message message(buffer, len);
        printf("This is the action: %s", buffer);
        u_int32_t data = message.toBytes(buffer, sizeof(u_int32_t));
        sendMessage(data, len);
    }
    free(buffer);
    fclose(archivo);
    return 0;
}

int Client::sendMessage(u_int32_t message, size_t size){
    printf("This is the message in decimals: %d\n", message);
    printf("This is the message in hex: %X\n", message);
    //socket.sendData((char*) &message, size);
    return 0;
}

/*
int Client::recieveMessage(const char* buffer);
int Client::printStatus(const char* recievedStatus);
int Client::closeConnection();
*/
Client::~Client(){
    //socket.disconnect(); 
}

int main(int argc, char* argv[]){
    if (argc != 4){
        printf("Error: invalid number of arguments");
        return -1;
    }

    char* ip = argv[1];
    char* port = argv[2];
    char* path = argv[3];

    Client client(ip, port);
    client.readFromFile(path);

//    client.closeConnection();
    return 0;
}