#include "Semaphore_c.h"

using namespace std;

void Semaphore_c::acquire(){
    unique_lock<mutex> ul{mtx};
    not_empty.wait(ul, [this](){return (cnt > 0);});
    
    cnt--;
    not_full.notify_one();
}

void Semaphore_c::release(){
    unique_lock<mutex> ul{mtx};
    not_full.wait(ul, [this](){return (cnt < MAX);});

    cnt++;
    not_empty.notify_one();
}

int Semaphore_c::available_permits(){
    return cnt;
}