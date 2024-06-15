#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

//Web Server Class
class WebServer {
private:
    bool isBusy; //Variable to determine if current webserver is busy
    int timeRemaining; //Time remaining for request to process
public:
    WebServer();
    bool request_process(const Request& req); //Process Request
    int getTime(); //Get time reminaing for server to process request
    void time_tick(); //Count down for process
    bool is_server_available() const; //Bool to determine if server is available or not
    
};

#endif
