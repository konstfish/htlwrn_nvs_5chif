#include "Philosopher.h"
#include "CLI11.hpp"

using namespace std;

int main(int argc, char** argv) {
    // 5 gabeln

    CLI::App app("Dining philosophers simulation");

    int deadlock_prevention{1};
    int livelock{0};

    app.add_option("-n,--nodeadlock", deadlock_prevention, "Prevent a deadlock at all",true);
    app.add_option("-l,--livelock", livelock, "Simulate a livelock",true);

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) { 
        return app.exit(e);
    }


    timed_mutex p1_p2;
    timed_mutex p2_p3;
    timed_mutex p3_p4;
    timed_mutex p4_p5;
    timed_mutex p5_p1;

    Philosopher p1(1, ref(p1_p2), ref(p5_p1), deadlock_prevention, livelock);
    Philosopher p2(2, ref(p2_p3), ref(p1_p2), deadlock_prevention, livelock);
    Philosopher p3(3, ref(p3_p4), ref(p2_p3), deadlock_prevention, livelock);
    Philosopher p4(4, ref(p4_p5), ref(p3_p4), deadlock_prevention, livelock);
    Philosopher p5(5, ref(p5_p1), ref(p4_p5), deadlock_prevention, livelock);

    thread tp1{ref(p1)};
    thread tp2{ref(p2)};
    thread tp3{ref(p3)};
    thread tp4{ref(p4)};
    thread tp5{ref(p5)};

    tp1.join();
    tp2.join();
    tp3.join();
    tp4.join();
    tp5.join();

    return 0;
}