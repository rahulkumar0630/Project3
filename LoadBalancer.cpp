#include "LoadBalancer.h"
#include <iostream>

LoadBalancer::LoadBalancer(int startingServers, const std::string& file_log_name) : internal_clock(0) {
    //Add all the initial servers to the queue
    for (int i = 0; i < startingServers; ++i) {
        Web_Servers.push_back(new WebServer());
    }

    initialServersFromConstructor = startingServers; //Set staring servers
    hasReachedEndOfInitialQueue = false; //Set that initial queue is not empty

    file_log.open(file_log_name); //Open file

    //Failed to open file
    if (!file_log.is_open()) {
        std::cerr << "Log File Failed to Open\n";
        exit(1);
    }
    
}

//Removes all entities
LoadBalancer::~LoadBalancer() {
    for (auto server : Web_Servers) {
        delete server;
    }
    if (file_log.is_open()) {
        file_log.close();
    }
}


void LoadBalancer::add_server() {
    Web_Servers.push_back(new WebServer()); //Adds server
}

void LoadBalancer::remove_server() {
    if (!Web_Servers.empty()) { //if not empty, delete the element
        delete Web_Servers.back(); //Deallocation
        Web_Servers.pop_back();
    }
}


bool LoadBalancer::areAllServersBusy() const {
    for (const auto& server : Web_Servers) { //Checks all servers
        if (server->is_server_available()) { //If server is available, then return false
            return false;
        }
    }
    return true; //All servers are busy
}


void LoadBalancer::add_request(const Request& req) {
    queueForRequests.request_add(req); //Add request to queue
}

void LoadBalancer::remove_specified_server(WebServer* serverToRemove) {
    auto it = std::find(Web_Servers.begin(), Web_Servers.end(), serverToRemove); //Finds all servers and assigns it
    if (it != Web_Servers.end()) {
        delete *it; //Deletes the specified server (Deallocation)
        Web_Servers.erase(it); //Removes from Queue
    }
}

//This function servers to remove excessive servers that were added. It will remove avaliable servers as others
//are still processing requests.
void LoadBalancer::removeExcessiveAvaliableServers() {
    WebServer* server_to_remove = nullptr; 

    for (const auto& server : Web_Servers) {
        if (server->is_server_available()) { //Finds first available server
            server_to_remove = server;
        }
    }
    //If found
    if (server_to_remove != nullptr) {
        file_log << "Removing Excessive Available Server...  " << "\n";
        remove_specified_server(server_to_remove); //Uses specified server function to remove.
    }
}

//Check if any server will process requests soon.
bool LoadBalancer::checkIfAnyServersWillBeAvaliableInTime(int time){
    for (const auto& server : Web_Servers) {
        if(server->getTime() <= 10){ //If there is a server that will process a request in 10 seconds or less
            return true;
        }
    }
    return false;
}

//This is for allocating the requests to the servers
void LoadBalancer::allocate_requests_to_web_servers() {
    Request req = queueForRequests.request_get(); //Get latest request
    int staticSize = Web_Servers.size();

    if(staticSize > 15){ // If we have added up to 15 servers to mitigate load
        removeExcessiveAvaliableServers(); //Remove the excess based on availability 
    }

    //There is no server available yet, it is now waiting for available servers
    if(areAllServersBusy()){
        file_log << "Request Time for Completion: " << req.amount_time  << "\n";
        file_log << "Request IP Address In: " << req.ip_address_IN  << "\n";
        file_log << "Request IP Address Out: " << req.ip_address_OUT  << "\n";
        file_log << "\n";
    }

    //First, if all servers are busy, and there will be no timely server available, and the request will take a long time.
    //Then we can add a server, because we need to take care of this request soon. Otherwise, we will waste a lot of clock
    //time.
    if (areAllServersBusy() && checkIfAnyServersWillBeAvaliableInTime(req.amount_time) == false && req.amount_time >= 75) {
        add_server();
    } 

    //If the initial queue is empty
    if(queueForRequests.is_empty()){
        if(staticSize > initialServersFromConstructor){ //Reduce back to initial 
            removeExcessiveAvaliableServers();
        }    
    }
    
    //Taking care of request
    for (auto& server : Web_Servers) {
        if (server->is_server_available() && !queueForRequests.is_empty()) { //If there is an available server
            file_log << "Took Care of Request with Time: " << queueForRequests.request_get().amount_time << "\n";
            file_log << "Request IP Address In: " << queueForRequests.request_get().ip_address_IN  << "\n";
            file_log << "Request IP Address Out: " << queueForRequests.request_get().ip_address_OUT  << "\n";
            file_log << "\n";
            server->request_process(queueForRequests.request_pop()); //Process Request
            
        }
    }
    
    


}

//Generate random IP
std::string generateRandomIP() {
    return std::to_string(rand() % 256) + "." + 
           std::to_string(rand() % 256) + "." + 
           std::to_string(rand() % 256) + "." + 
           std::to_string(rand() % 256);
}

//Function to write to log
void LoadBalancer::share_log_status() {
    file_log << "\n";
    file_log << "Post Request Log: " << "\n";
    file_log << "Internal Clock: " << internal_clock << "\n";
    file_log << "Size of Queue: " << (queueForRequests.is_empty() ? 0 : queueForRequests.size_of_queue()) << "\n"; 

    for (size_t i = 0; i < Web_Servers.size(); ++i) {
        if(Web_Servers[i]->is_server_available()){
             file_log << "Server " << i << " is available\n";
        } else {
            file_log << "Server " << i << " is busy ... available in... " << Web_Servers[i]->getTime() << "\n";
        }
    }

    file_log << "\n";
}

//Start load balancer
void LoadBalancer::start_load_balancer(int dur) {

    for (int i = 0; i < dur; i++) {
        internal_clock++;
        allocate_requests_to_web_servers();

        for (auto& server : Web_Servers) {
            server->time_tick();
        }

        //Generate random requests during the clock cycle
        if (rand() % 10 == 0) {
            Request req = {generateRandomIP(), generateRandomIP(), (rand() % 100) + 1};
            add_request(req);
        }

        share_log_status();
    }
}
