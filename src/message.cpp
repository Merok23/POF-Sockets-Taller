#include "message.h"

Message::Message(const char* message, const size_t len){
    this->message = (char*) malloc(len);
    strncpy(this->message, message, len);
    this->len = len;
}

int countSpaces(const char* message, const int len);

int countSpaces(const char* message, const int len){
    int spaces = 0;
    for(int i = 0; i < len; i++) if(message[i] == ' ') spaces++;
    return spaces;
}

u_int32_t Message::toBytes(const char* message, const size_t len){
    //separar en palabras
    int espacios = countSpaces(message, this->len);
    u_int32_t data;
    switch (espacios) { //Esto es horrible, hay que refaccionar en clases con polimofirmo. (como se hace en C?)
        case 0: {
            u_int32_t nop = 0x0000;
            u_int32_t reload = 0x0300;
            if(strstr(message, "NOP") != 0) data = nop;
            if(strstr(message, "Reload") != 0) data = reload;
            return(data);
            break;
        }
        case 1: {// shooting pues tiene 1 espacio
            u_int32_t disparando = 0x0101; // Shooting 1
            u_int32_t deja_disparar = 0x0100; // Shooting 0
            if(strstr(message, "0") != 0) data = deja_disparar;
            else data = disparando;
            return(data);
        }
        case 2:{
            u_int32_t moving_up = 0x0200; // Moving up 0 1
            u_int32_t moving_down = 0x0201; // Moving down 0 -1
            u_int32_t moving_left = 0x0210; // Moving left -1 0
            u_int32_t moving_right = 0x0211; // Moving right 1 0

            if(strstr(message, "0 1") != 0) data = moving_up;
            else if(strstr(message, "0 -1") != 0) data = moving_down;
            else if(strstr(message, "-1 0") != 0) data = moving_left;
            else if(strstr(message, "1 0") != 0) data = moving_right;
            return(data);
        }
        default:{
            std::cout << "Error: invalid message" << std::endl;
            break;
        }    
    }
    //traducir a bytes
    return 0;
}
/*
int Message::countSpaces(const char* message, const size_t len){
    int spaces = 0;
    for(int i = 0; i < len; i++){
        if(message[i] == ' ') spaces++;
    }
    return spaces;
}
*/
Message::~Message(){
    free(this->message);
}