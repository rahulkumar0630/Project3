#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <fstream>
#include "RequestQueue.h"
#include "WebServer.h"

class LoadBalancer {
private:
    std::vector<WebServer*> Web_Servers; 
    int internal_clock;
    int initialServersFromConstructor = 0;
    RequestQueue queueForRequests;
    std::ofstream file_log;

    bool areAllServersBusy() const; 
    bool checkIfAnyServersWillBeAvaliableInTime(int time);
    bool anyServerAboutToBeCompleted() const;
    bool hasReachedEndOfInitialQueue = false;

    void removeExcessiveAvaliableServers();
    void add_server();
    void remove_server();
    void remove_specified_server(WebServer* serverToRemove);

public:
    LoadBalancer(int startingServers, const std::string& file_log_name);
    ~LoadBalancer();
    void add_request(const Request& req);
    void allocate_requests_to_web_servers();
    void start_load_balancer(int duration);
    void share_log_status();
};

#endif 
