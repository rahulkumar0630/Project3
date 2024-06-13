#include "WebServer.h"

WebServer::WebServer() : isBusy(false), timeRemaining(0) {}

bool WebServer::request_process(const Request& req) {
    if (!isBusy) {
        isBusy = true;
        timeRemaining = req.amount_time;
        return true;
    }
    return false;
}

int WebServer::getTime(){
    return timeRemaining;
}

void WebServer::time_tick() {
    if (isBusy) {
        timeRemaining--;
        if (timeRemaining <= 0) {
            isBusy = false;
        }
    }
}

bool WebServer::is_server_available() const {
    return !isBusy;
}

