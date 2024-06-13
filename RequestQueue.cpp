#include "RequestQueue.h"

void RequestQueue::request_add(const Request& req) {
    requests.push(req);
}

Request RequestQueue::request_pop() {
    if (!requests.empty()) {
        Request req = requests.front();
        requests.pop();
        return req;
    }
    return {}; 
}

Request RequestQueue::request_get() {
    if (!requests.empty()) {
        Request req = requests.front();
        return req;
    }
    return {}; 
}


int RequestQueue::size_of_queue() const { 
    return requests.size();
}

bool RequestQueue::is_empty() const {
    return requests.empty();
}
