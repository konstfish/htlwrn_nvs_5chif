#include <iostream>
#include <thread>
#include <random>
#include <iomanip>
#include <sstream>

#include "work_queue.h"

using namespace std;

void worker(int id, WorkQueue& q);

/*
./loadsim | grep -v "B: "
gute hilfe beim debuggen
*/

int main() {
    WorkQueue wq;

    int cnt{1};

    thread t1{worker, 1, ref(wq)};
    thread t2{worker, 2, ref(wq)};
    thread t3{worker, 3, ref(wq)};

    random_device rd;
    std::mt19937 gen{rd()}; std::uniform_real_distribution<> dis{0, 1};
    double seconds;

    cout << setprecision(2);

    while(true){
        cout << "B: Waiting to submit work packet" << cnt << endl;

        seconds = dis(gen);
        this_thread::sleep_for(chrono::milliseconds{(int)(seconds * 1000)});

        WorkPacket tmp(cnt);
        wq.push(tmp);
        cout << "B: Submitted work packet " << tmp.getId() << " (" << seconds << "s)" << endl;
        cnt += 1;
    }

    t1.join();
    t2.join();
    t3.join();

    return 0;
}

void worker(int id, WorkQueue& q){
    ostringstream buf;
    string tmpstr;

    random_device rd;
    std::mt19937 gen{rd()}; std::uniform_real_distribution<> dis{1, 10};
    double seconds;

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

            seconds = dis(gen);
            this_thread::sleep_for(chrono::milliseconds{(int)(seconds * 1000)});

            buf << setprecision(2);
            buf << "W" << id << ": Processed work packet " << tmp.getId() << " (" << seconds << "s)" << "\n";
            tmpstr = buf.str();
            buf.str("");
            cout << tmpstr;
        }
    }
}