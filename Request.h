#ifndef REQUEST_H
#define REQUEST_H

#include <string>

struct Request {
    std::string ip_address_IN;
    std::string ip_address_OUT;
    int amount_time; 
};

#endif // REQUEST_H
