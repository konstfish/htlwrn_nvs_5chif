#include <iostream>
#include <thread>
#include <sstream>

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

    void set_latency(long lat){
        p1.set_latency(lat);
        p2.set_latency(lat);
    }

};

class TimeSlave{
    private:

    std::string name;
    Clock c;
    Channel *chan = new Channel();

    public:

    TimeSlave(std::string rn, int hours, int minutes, int seconds, long latency):name( rn ){
        c = Clock(name, hours, minutes, seconds);

        (*chan).set_latency(latency);
    };

    void operator()(){
        thread clock{ref(c)};

        long value;
        long diff;

        while(true){
            (*chan).get_pipe1() >> value;

            diff = c.to_time() - value;

            (*chan).get_pipe2() << diff;

            (*chan).get_pipe1() >> value;

            value += c.to_time();

            c.from_time(value);
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
        thread clock{ref(c)};

        Pipe<long> &in_s1 = (*slave_chan1).get_pipe1();
        Pipe<long> &out_s1 = (*slave_chan1).get_pipe2();

        Pipe<long> &in_s2 = (*slave_chan2).get_pipe1();
        Pipe<long> &out_s2 = (*slave_chan2).get_pipe2();

        long s1_diff;
        long s2_diff;

        long s1_avg;
        long s2_avg;

        long m_avg;

        ostringstream buf;

        while(true){
            // step 1 send time

            cout << "Starting Berkely Alg\n";

            m_avg = c.to_time();

            in_s1 << m_avg;
            in_s2 << m_avg;

            // step 2 get diffs

            out_s1 >> s1_diff;
            out_s2 >> s2_diff;

            // step 3 avg times

            m_avg = (s1_diff + s2_diff) / 3;
            s1_avg = m_avg - s1_diff;
            s2_avg = m_avg - s2_diff;


            buf << "Calculated Diffs:\nMaster: " << m_avg << "\nSlave1: " << s1_avg << "\nSlave2: " << s1_avg << endl; 
            cout << buf.str();
            buf.str("");

            m_avg += c.to_time();

            c.from_time(m_avg);

            in_s1 << s1_avg;
            in_s2 << s2_avg;

            cout << "Updated Clocks.\n";

            this_thread::sleep_for(10s);
        }

        in_s1.close();
        out_s1.close();
        in_s2.close();
        out_s2.close();

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

    TimeSlave slave1("slave1", 1, 2, 50, 1);
    TimeSlave slave2("slave2", 1, 3, 25, 2);

    TimeMaster master1("master1", 1, 3, 0);

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