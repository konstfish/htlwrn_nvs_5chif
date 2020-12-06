#include <iostream>
#include <thread>

#include "clock.h"

using namespace std;

int main() {
    thread clock{Clock("testclock")};
    clock.join();


    return 0;
}
