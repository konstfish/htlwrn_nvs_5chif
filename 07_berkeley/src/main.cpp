#include <iostream>
#include <thread>

#include "clock.h"

using namespace std;

class TimeSlave{
    private:

    std::string name;
    Clock c;

    public:

    TimeSlave(std::string rn, int hours, int minutes, int seconds):name( rn ){
        c = Clock(name, hours, minutes, seconds);
    };

    void operator()(){

    };
};

int main() {
    thread clock{Clock("testclock")};

    thread clock2{Clock("testclock2", 1, 1, 1)};

    clock.join();
    clock2.join();

    return 0;
}