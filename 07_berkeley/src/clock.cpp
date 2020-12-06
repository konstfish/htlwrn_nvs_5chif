#include "clock.h"

using namespace std;

void Clock::operator()(){
    ostringstream buf;

    while(true){
        buf << name << ": " << curr_time << endl;
        cout << buf.str();
        buf.str("");

        curr_time += std::chrono::seconds(1);
        this_thread::sleep_for(std::chrono::milliseconds(second_step));
    }

}

void Clock::set_time(int hours, int minutes, int seconds){
    curr_time = ::set_time(curr_time, hours, minutes, seconds);
}

std::tuple<int, int, int> Clock::get_time(){
    return ::get_time(curr_time);
}

long Clock::to_time(){
    return std::chrono::system_clock::to_time_t(curr_time);
}

void Clock::from_time(long time){
    curr_time = chrono::system_clock::from_time_t(time);
}

void Clock::debug_out(){
    ostringstream buf;

    buf << name << ": " << curr_time << endl;
    cout << buf.str();
    buf.str("");
}