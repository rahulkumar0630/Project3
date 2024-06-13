#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

class WebServer {
private:
    bool isBusy;
    int timeRemaining;
public:
    WebServer();
    bool request_process(const Request& req);
    int getTime();
    void time_tick();
    bool is_server_available() const;
    
};

#endif
