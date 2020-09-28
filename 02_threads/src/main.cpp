#include <iostream>
#include <thread>

using namespace std;

void mini_jcw();

int main() {
    thread t{mini_jcw};
    t.join();
    cout << t.joinable() << endl;
}

void mini_jcw(){
    int round = 0;
    while (true) {
        this_thread::sleep_for(1s);
        round += 1;
        cout << round << " MINI F56 JCW" << endl;     
    }
}