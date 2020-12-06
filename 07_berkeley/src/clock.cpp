#include "clock.h"

#include "timeutils.h"

using namespace std;

void Clock::operator()(){
    while(true){
        cout << name << ": " << curr_time << endl;

        curr_time += std::chrono::seconds(1);

        this_thread::sleep_for(1s);
    }

}