#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <queue>
#include "Request.h"

class RequestQueue {
private:
    std::queue<Request> requests;
public:
    void request_add(const Request& req);
    Request request_pop();
    Request request_get();
    int size_of_queue() const; 
    bool is_empty() const;
    
};

#endif 
