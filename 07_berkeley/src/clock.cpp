#include "clock.h"

using namespace std;

void Clock::operator()(){
    ostringstream buf;

    while(true){
        buf << name << ": " << curr_time << endl;
        cout << buf.str();
        buf.str("");

        curr_time += std::chrono::seconds(1);

        this_thread::sleep_for(1s);
    }

}