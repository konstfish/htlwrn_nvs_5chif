#pragma once

#include <iostream>
#include <queue> 
#include <mutex>

#include "work_packet.h"

class WorkQueue{
    private:
        std::queue<WorkPacket> q;
        size_t cap;

        std::mutex m;
        std::condition_variable not_empty;
        std::condition_variable not_full;

    public:
    WorkQueue(size_t capacity);

    void push(WorkPacket pk);
    WorkPacket pop();

};
