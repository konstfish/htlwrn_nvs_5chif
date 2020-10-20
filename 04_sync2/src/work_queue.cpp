#include "work_queue.h"

using namespace std;

WorkQueue::WorkQueue(size_t capacity){
    cap = capacity;
}

void WorkQueue::push(WorkPacket pk){
    unique_lock lck(m);
    not_full.wait(lck, [this]() { return q.size() < cap; });
    q.push(pk);
    not_empty.notify_one();
}

WorkPacket WorkQueue::pop(){
    unique_lock lck(m);
    not_empty.wait(lck, [this]() { return !q.empty(); });

    WorkPacket temp = q.front();
    q.pop();
    
    not_full.notify_one();

    return temp;
}