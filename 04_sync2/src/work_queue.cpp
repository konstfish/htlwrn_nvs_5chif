#include "work_queue.h"

WorkQueue::WorkQueue(){
}

void WorkQueue::push(WorkPacket pk){
    q.push(pk);
}

WorkPacket WorkQueue::pop(){
    if(q.size() > 0){
        WorkPacket temp = q.front();
        q.pop();
        return temp;
    }
    WorkPacket temp{-1};
    return temp;
}