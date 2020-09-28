#include <iostream>
#include <thread>
#include <random>
#include <iomanip>

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
        string round_delay;

        random_device rd;


        while (true) {
            std::mt19937 gen{rd()}; std::uniform_real_distribution<> dis{1, 10};
            this_thread::sleep_for(chrono::milliseconds{(int)(dis(gen) * 1000)});
            round += 1;
            tmp = to_string(round) + " " + name + " " + to_string(dis(gen)) + "s\n";
            cout << tmp;
        }
    }
};

int main() {
    cout << setprecision(3);
    cout << 3.231 << endl;

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