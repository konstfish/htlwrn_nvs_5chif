#include <iostream>
#include <thread>

#include "work_queue.h"

using namespace std;

int main() {
    WorkQueue wq;

    int cnt{1};

    while(true){
        this_thread::sleep_for(chrono::milliseconds{500});
        WorkPacket tmp(cnt);
        wq.push(tmp);
        cout << "B: Submitted work packet " << tmp.getId() << endl;
        cnt += 1;
    }

    return 0;
}
