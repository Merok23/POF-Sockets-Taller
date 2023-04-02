#include <stdlib.h>
#include <string.h>
#include <iostream>

class Message{
    private:
        char* message;
        size_t len;
        int messageType;
    public:

        Message(const char* message, const size_t len);


    //    int Message::countSpaces(const char* message, const size_t len);

        u_int32_t toBytes(const char* message, const size_t len);

    //    bool isValid() = 0; //this is a pure virtual function that will be implemented in the child classes

        ~Message();
};