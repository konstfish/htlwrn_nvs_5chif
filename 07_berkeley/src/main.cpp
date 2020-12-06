#include <iostream>
#include <thread>

#include "clock.h"

using namespace std;

int main() {
    thread clock{Clock("testclock")};

    thread clock2{Clock("testclock2", 1, 1, 1)};

    clock.join();
    clock2.join();

    return 0;
}
