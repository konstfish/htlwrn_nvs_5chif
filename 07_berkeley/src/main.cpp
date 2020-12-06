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
        thread clock{c};

        clock.join();
    };
};

class TimeMaster{
    private:

    std::string name;
    Clock c;

    public:

    TimeMaster(std::string rn, int hours, int minutes, int seconds):name( rn ){
        c = Clock(name, hours, minutes, seconds);
    };

    void operator()(){
        thread clock{c};

        clock.join();
    };
};

int main() {
    thread s1{TimeSlave("slave1", 1, 1, 1)};
    thread s2{TimeSlave("slave2", 1, 1, 1)};

    thread m1{TimeMaster("master1", 1, 1, 1)};

    s1.join();
    s2.join();

    m1.join();

    return 0;
}