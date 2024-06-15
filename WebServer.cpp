#include "WebServer.h"

WebServer::WebServer() : isBusy(false), timeRemaining(0) {}

bool WebServer::request_process(const Request& req) {
    //It not busy, assign request to this server and set time to the request time
    if (!isBusy) {
        isBusy = true;
        timeRemaining = req.amount_time;
        return true;
    }
    return false; // Server is busy
}

//Return time left for server to process request
int WebServer::getTime(){
    return timeRemaining;
}

//Reduce time remaining for the request
void WebServer::time_tick() {
    if (isBusy) {
        timeRemaining--;
        if (timeRemaining <= 0) {
            isBusy = false;
        }
    }
}

//Check if request is processed
bool WebServer::is_server_available() const {
    return !isBusy;
}

