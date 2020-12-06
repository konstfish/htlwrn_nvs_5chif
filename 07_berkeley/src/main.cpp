#include <iostream>
#include <thread>

#include "clock.h"

#include "pipe.h"

using namespace std;

class Channel{
    private:
    Pipe<long> p1;
    Pipe<long> p2;

    public:

    Channel(){};

    Pipe<long>& get_pipe1(){
        return p1;
    }

    Pipe<long>& get_pipe2(){
        return p2;
    }

};

class TimeSlave{
    private:

    std::string name;
    Clock c;
    Channel *chan = new Channel();

    public:

    TimeSlave(std::string rn, int hours, int minutes, int seconds):name( rn ){
        c = Clock(name, hours, minutes, seconds);
    };

    void operator()(){
        thread clock{c};

        clock.join();
    };

    Channel* get_channel(){
        return chan;
    }
};

class TimeMaster{
    private:

    std::string name;
    Clock c;

    Channel *slave_chan1;
    Channel *slave_chan2;

    public:

    TimeMaster(std::string rn, int hours, int minutes, int seconds):name( rn ){
        c = Clock(name, hours, minutes, seconds);
    };

    void operator()(){
        thread clock{c};

        clock.join();
    };

    void set_channel1(Channel* sc1){
        slave_chan1 = sc1;
    }

    void set_channel2(Channel* sc2){
        slave_chan2 = sc2;
    }
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