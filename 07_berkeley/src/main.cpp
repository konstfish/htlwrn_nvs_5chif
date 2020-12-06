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

        long value;

        for(int i = 0; i < 3; i++){
            (*chan).get_pipe1() >> value;
            cout << value << endl;
        }
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

        for(int i = 0; i < 3; i++){
            (*slave_chan1).get_pipe1() << 1;
            (*slave_chan2).get_pipe1()  << 2;

            this_thread::sleep_for(500ms);
        }

        (*slave_chan1).get_pipe1().close();
        (*slave_chan2).get_pipe1().close();

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

    TimeSlave slave1("slave1", 1, 1, 1);
    TimeSlave slave2("slave2", 1, 1, 1);

    TimeMaster master1("master1", 1, 1, 1);

    master1.set_channel1(slave1.get_channel());
    master1.set_channel2(slave2.get_channel());

    thread ts1{slave1};
    thread ts2{slave2};

    thread tm1{master1};

    ts1.join();
    ts2.join();

    tm1.join();

    return 0;
}