#ifndef RESOLVER_H
#define RESOLVER_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
//Resolver del profesor, literalmente copiado y pegado porque necesito un poco de abstraccion por dio y no tengo tiempo

class Resolver {
    private:
    struct addrinfo *result;
    struct addrinfo *_next;

    public:
    

        Resolver(const char* hostname, const char* servname, bool is_passive);


        Resolver(const Resolver&) = delete;
        
        Resolver& operator=(const Resolver&) = delete;
        
        Resolver(Resolver&&);
        
        Resolver& operator=(Resolver&&);

        bool hasNext();

       
        struct addrinfo* next();

        
        ~Resolver();
};
#endif