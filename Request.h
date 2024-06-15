#ifndef REQUEST_H
#define REQUEST_H

#include <string>

//Request Struct
struct Request {
    std::string ip_address_IN; //IP address for IN
    std::string ip_address_OUT; //IP address for OUT
    int amount_time; //Request Processing time
};

#endif 
