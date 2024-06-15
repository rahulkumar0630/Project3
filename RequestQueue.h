#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <queue>
#include "Request.h"

class RequestQueue {
private:
    std::queue<Request> requests; //Queue for requests
public:
    void request_add(const Request& req); //Add request to queue
    Request request_pop(); //Remove request from Queue
    Request request_get(); //Return information for current Request
    int size_of_queue() const; //Return Size of Queue
    bool is_empty() const; //Check if Queue is empty
    
};

#endif 
