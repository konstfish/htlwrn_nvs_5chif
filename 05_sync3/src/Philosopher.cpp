#include "Philosopher.h"

using namespace std;

void Philosopher::operator()(){
    while(true){
        cout << "Philosopher " << id << " is thinking..." << endl;
        this_thread::sleep_for(1s);

        cout << "Philosopher " << id << " attempts to get left fork" << endl;
        linke_gabel.lock();

        cout << "Philosopher " << id <<  " got left fork. Now he wants the right one..." << endl;

        rechte_gabel.lock();

        cout << "Philosopher " << id <<  " got right fork. Now he is eating..." << endl;
        this_thread::sleep_for(2s);

        cout << "Philosopher" << id << " finished eating" << endl;

        linke_gabel.unlock();
        cout << "Philosopher " << id <<  " released left fork" << endl;

        rechte_gabel.unlock();
        cout << "Philosopher " << id <<  " released right fork" << endl;
    }
}