#include "Philosopher.h"

using namespace std;

void Philosopher::operator()(){
    ostringstream buf;

    while(true){

        buf << "Philosopher " << id << " is thinking..." << endl;
        cout << buf.str();
        buf.str("");

        this_thread::sleep_for(1s);

        buf << "Philosopher " << id << " attempts to get left fork" << endl;
        cout << buf.str();
        buf.str("");
        linke_gabel.lock();

        buf << "Philosopher " << id <<  " got left fork. Now he wants the right one..." << endl;
        cout << buf.str();
        buf.str("");
        rechte_gabel.lock();

        buf << "Philosopher " << id <<  " got right fork. Now he is eating..." << endl;
        cout << buf.str();
        buf.str("");

        this_thread::sleep_for(2s);

        buf << "Philosopher" << id << " finished eating" << endl;
        cout << buf.str();
        buf.str("");

        linke_gabel.unlock();
        buf << "Philosopher " << id <<  " released left fork" << endl;
        cout << buf.str();
        buf.str("");

        rechte_gabel.unlock();
        buf << "Philosopher " << id <<  " released right fork" << endl;
        cout << buf.str();
        buf.str("");
    }
}