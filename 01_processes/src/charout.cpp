/*
    FISCHER David
*/

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace std;

int main(int argc, char **argv) {
    cout << argc << endl;
    std::chrono::milliseconds sleeptime(500);

    while (true) {
        cout << argv[1];
        cout << flush;
        this_thread::sleep_for(sleeptime);
    }
}