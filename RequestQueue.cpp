#include "RequestQueue.h"

//Push a request into the RequestQueue
void RequestQueue::request_add(const Request& req) {
    requests.push(req);
}

//Get the first request in the queue and remove it
Request RequestQueue::request_pop() {
    if (!requests.empty()) {
        Request req = requests.front();
        requests.pop();
        return req;
    }
    return {}; 
}

//Get the first request in the queue
Request RequestQueue::request_get() {
    if (!requests.empty()) {
        Request req = requests.front();
        return req;
    }
    return {}; 
}

//Return size of queue
int RequestQueue::size_of_queue() const { 
    return requests.size();
}

//Return is queue is empty or not
bool RequestQueue::is_empty() const {
    return requests.empty();
}
