#include <iostream>
#include <thread>
#include <random>
#include <iomanip>
#include <sstream>

#include "work_queue.h"

using namespace std;

void worker(int id, WorkQueue& q);

int main() {
    WorkQueue wq;

    int cnt{1};

    thread t1{worker, 1, ref(wq)};
    thread t2{worker, 2, ref(wq)};


    while(true){
        WorkPacket tmp(cnt);
        wq.push(tmp);
        cout << "B: Submitted work packet " << tmp.getId() << endl;
        cnt += 1;
        this_thread::sleep_for(chrono::milliseconds{500});
    }

    return 0;
}


void worker(int id, WorkQueue& q){
    ostringstream buf;
    string tmpstr;
    while(true){
        WorkPacket tmp = q.pop();
        if(tmp.getId() == -1){
            buf << "W" << id << ": Want work packet\n";
            tmpstr = buf.str();
            buf.str("");
            cout << tmpstr;
            this_thread::sleep_for(chrono::milliseconds{500});
        }else{
            buf << "W" << id << ": Got work packet " << tmp.getId() << "\n";
            tmpstr = buf.str();
            buf.str("");
            cout << tmpstr;

            this_thread::sleep_for(chrono::milliseconds{1000});

            buf << "W" << id << ": Processed work packet " << tmp.getId() << "\n";
            tmpstr = buf.str();
            buf.str("");
            cout << tmpstr;
        }
    }
}