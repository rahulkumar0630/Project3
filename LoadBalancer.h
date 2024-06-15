#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <fstream>
#include "RequestQueue.h"
#include "WebServer.h"

class LoadBalancer {
private:
    std::vector<WebServer*> Web_Servers; //Web Server vector for the LoadBalancer
    int internal_clock; //Internal Clock to represent clock Cycles
    int initialServersFromConstructor = 0; //Starting Servers
    RequestQueue queueForRequests; //Request Queue
    std::ofstream file_log; //Log File

    bool areAllServersBusy() const; //Check if servers are busy
    bool checkIfAnyServersWillBeAvaliableInTime(int time); //Check if servers will be available in the near future
    bool anyServerAboutToBeCompleted() const; 
    bool hasReachedEndOfInitialQueue = false; //Check if initial request queue is empty

    void removeExcessiveAvaliableServers(); //Remove excessive servers
    void add_server(); //Add server
    void remove_server(); //Remove server
    void remove_specified_server(WebServer* serverToRemove); //Remove a specific server from queue

public:
    LoadBalancer(int startingServers, const std::string& file_log_name); //Constructor
    ~LoadBalancer(); //Deconstructor
    void add_request(const Request& req); // Add a request to queue
    void allocate_requests_to_web_servers(); //Allocate the requests to the web servers
    void start_load_balancer(int duration); //Start the load balancer
    void share_log_status(); //Update log
};

#endif 
