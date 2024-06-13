#include <iostream>
#include <cstdlib>
#include <ctime>
#include "LoadBalancer.h"


inline std::string randomIPAddress() {
    return std::to_string(rand() % 256) + "." + 
    std::to_string(rand() % 256) + "." + 
    std::to_string(rand() % 256) + "." + 
    std::to_string(rand() % 256);
}

int main() {
    srand(time(0));
    int total_duration, startingServers;

    std::cout << "Number of Web Servers (Initial): ";
    std::cin >> startingServers;
    std::cout << "Clock Cycles of Load Balancer (clock cycles): ";
    std::cin >> total_duration;

    LoadBalancer load_balancer(startingServers, "log_load_balancer.txt");
    
    for (int i = 0; i < 100 * startingServers; i++) {
        Request req = {randomIPAddress(), randomIPAddress(), (rand() % 100) +1};
        load_balancer.add_request(req);
    }

    load_balancer.start_load_balancer(total_duration);

    std::cout << "Successful Load Balancing Simulation. Output located in log_load_balancer.txt\n";

    return 0;
}
