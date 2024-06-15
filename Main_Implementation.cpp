#include <iostream>
#include <cstdlib>
#include <ctime>
#include "LoadBalancer.h"


//Generate random IP address
inline std::string randomIPAddress() {
    return std::to_string(rand() % 256) + "." + 
    std::to_string(rand() % 256) + "." + 
    std::to_string(rand() % 256) + "." + 
    std::to_string(rand() % 256);
}

int main() {
    srand(time(0)); //Start time for main
    int total_duration, startingServers; //Variables for Clock Time and Amount of servers

    //User input for web servers and clock cycles
    std::cout << "Number of Web Servers (Initial): ";
    std::cin >> startingServers;
    std::cout << "Clock Cycles of Load Balancer (clock cycles): ";
    std::cin >> total_duration;

    //Initialize Load Balancer
    LoadBalancer load_balancer(startingServers, "log_load_balancer.txt");
    
    //Generate 100 * the starting servers to create a request queue
    for (int i = 0; i < 100 * startingServers; i++) {
        Request req = {randomIPAddress(), randomIPAddress(), (rand() % 100) +1};
        load_balancer.add_request(req);
    }

    //Start load balancer
    load_balancer.start_load_balancer(total_duration);

    //Show that load balancer has completed.
    std::cout << "Successful Load Balancing Simulation. Output located in log_load_balancer.txt\n";

    return 0;
}
