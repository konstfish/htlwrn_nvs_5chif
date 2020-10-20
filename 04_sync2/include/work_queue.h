#pragma once

#include <iostream>
#include <queue> 

#include "work_packet.h"

class WorkQueue{
    private:
        std::queue<WorkPacket> q;
    public:
    WorkQueue();

    void push(WorkPacket pk);
    WorkPacket pop();

};
