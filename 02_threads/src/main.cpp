#include <iostream>
#include <thread>
#include <random>

using namespace std;

void mini_jcw();

class Car{
    public:
    string name;

    Car(string n){
        name = n;
    }

    void operator()(){
        int round = 0;
        string tmp;
        while (true) {
            //dis(gen)
            this_thread::sleep_for(1s);
            round += 1;
            tmp = to_string(round) + " " + name + "\n";
            cout << tmp;     
        }
    }
};

int main() {
    Car c1("MINI Cooper S");
    Car c2("MINI JCW");

    thread t1{c1};
    thread t2{c2};
    
    t1.join();
    t2.join();
    //thread t2{c2};
}

void mini_jcw(){
    int round = 0;
    while (true) {
        this_thread::sleep_for(1s);
        round += 1;
        cout << round << " MINI F56 JCW" << endl;     
    }
}