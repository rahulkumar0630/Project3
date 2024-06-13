#include "LoadBalancer.h"
#include <iostream>

LoadBalancer::LoadBalancer(int startingServers, const std::string& file_log_name) : internal_clock(0) {
    for (int i = 0; i < startingServers; ++i) {
        Web_Servers.push_back(new WebServer());
    }

    initialServersFromConstructor = startingServers;
    hasReachedEndOfInitialQueue = false;

    file_log.open(file_log_name);

    if (!file_log.is_open()) {
        std::cerr << "Log File Failed to Open\n";
        exit(1);
    }
    
}

LoadBalancer::~LoadBalancer() {
    for (auto server : Web_Servers) {
        delete server;
    }
    if (file_log.is_open()) {
        file_log.close();
    }
}


void LoadBalancer::add_server() {
    Web_Servers.push_back(new WebServer());
}

void LoadBalancer::remove_server() {
    if (!Web_Servers.empty()) {
        delete Web_Servers.back();
        Web_Servers.pop_back();
    }
}


bool LoadBalancer::areAllServersBusy() const {
    for (const auto& server : Web_Servers) {
        if (server->is_server_available()) {
            return false;
        }
    }
    return true;
}


void LoadBalancer::add_request(const Request& req) {
    queueForRequests.request_add(req);
}

void LoadBalancer::remove_specified_server(WebServer* serverToRemove) {
    auto it = std::find(Web_Servers.begin(), Web_Servers.end(), serverToRemove);
    if (it != Web_Servers.end()) {
        delete *it;
        Web_Servers.erase(it);
    }
}


void LoadBalancer::removeExcessiveAvaliableServers() {
    WebServer* server_to_remove = nullptr;

    for (const auto& server : Web_Servers) {
        if (server->is_server_available()) {
            server_to_remove = server;
        }
    }

    if (server_to_remove != nullptr) {
        file_log << "Removing Excessive Available Server...  " << "\n";
        remove_specified_server(server_to_remove);
    }
}


bool LoadBalancer::checkIfAnyServersWillBeAvaliableInTime(int time){
    for (const auto& server : Web_Servers) {
        if(server->getTime() <= 10){
            return true;
        }
    }
    return false;
}

void LoadBalancer::allocate_requests_to_web_servers() {
    Request req = queueForRequests.request_get();
    int staticSize = Web_Servers.size();

    if(staticSize > 15){
        removeExcessiveAvaliableServers();
    }

    if(areAllServersBusy()){
        file_log << "Request Time for Completion: " << req.amount_time  << "\n";
        file_log << "Request IP Address In: " << req.ip_address_IN  << "\n";
        file_log << "Request IP Address Out: " << req.ip_address_OUT  << "\n";
        file_log << "\n";
    }

    if (areAllServersBusy() && checkIfAnyServersWillBeAvaliableInTime(req.amount_time) == false && req.amount_time >= 75) {
        add_server();
    } 


    if(queueForRequests.is_empty()){
        if(staticSize > 10){
            removeExcessiveAvaliableServers();
        }    
    }
    

    for (auto& server : Web_Servers) {
        if (server->is_server_available() && !queueForRequests.is_empty()) {
            file_log << "Took Care of Request with Time: " << queueForRequests.request_get().amount_time << "\n";
            file_log << "Request IP Address In: " << queueForRequests.request_get().ip_address_IN  << "\n";
            file_log << "Request IP Address Out: " << queueForRequests.request_get().ip_address_OUT  << "\n";
            file_log << "\n";
            server->request_process(queueForRequests.request_pop());
            
        }
    }
    
    


}


std::string generateRandomIP() {
    return std::to_string(rand() % 256) + "." + 
           std::to_string(rand() % 256) + "." + 
           std::to_string(rand() % 256) + "." + 
           std::to_string(rand() % 256);
}


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

void LoadBalancer::start_load_balancer(int dur) {

    for (int i = 0; i < dur; i++) {
        internal_clock++;
        allocate_requests_to_web_servers();

        for (auto& server : Web_Servers) {
            server->time_tick();
        }

        if (rand() % 10 == 0) {
            Request req = {generateRandomIP(), generateRandomIP(), (rand() % 100) + 1};
            add_request(req);
        }

        share_log_status();
    }
}
