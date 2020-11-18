#include "Philosopher.h"

using namespace std;

std::mutex out_mtx;

void Philosopher::operator()(){
    ostringstream buf;

    while(true){

        println({"Philosopher ", to_string(id), " is thinking...\n"});
        this_thread::sleep_for(1s);

        println({"Philosopher ", to_string(id), " attempts to get left fork\n"});
        linke_gabel.lock();

        println({"Philosopher ", to_string(id), " got left fork. Now he wants the right one...\n"});
        rechte_gabel.lock();

        println({"Philosopher ", to_string(id), " got right fork. Now he is eating...\n"});
        this_thread::sleep_for(2s);
        println({"Philosopher ", to_string(id), " finished eating\n"});

        linke_gabel.unlock();
        println({"Philosopher ", to_string(id), " released left fork\n"});

        rechte_gabel.unlock();
        println({"Philosopher ", to_string(id), " released right fork\n"});
    }
}

void println(const std::initializer_list<std::string> &output){
    lock_guard<mutex> lg{out_mtx};
    for(string i : output){
        cout << i;
    }
}