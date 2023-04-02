#include "common_resolver.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

Resolver::Resolver( const char* hostname, const char* servname, bool is_passive) {
    struct addrinfo hints;
    this->result = this->_next = nullptr;

    memset(&hints, 0, sizeof(struct addrinfo)); //Initialize hints to 0
    hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
    hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
    hints.ai_flags = is_passive ? AI_PASSIVE : 0; 

    getaddrinfo(hostname, servname, &hints, &this->result);

    this->_next = this->result;
}

bool Resolver::hasNext() {
    return this->_next != NULL;
}

struct addrinfo* Resolver::next() {
    struct addrinfo *ret = this->_next;
    this->_next = ret->ai_next;
    return ret;
}

Resolver::~Resolver() {
    if (this->result) freeaddrinfo(this->result);
}