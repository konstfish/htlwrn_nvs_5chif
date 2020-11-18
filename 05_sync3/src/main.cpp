#include "Philosopher.h"

using namespace std;

int main() {
    // 5 gabeln

    mutex p1_p2;
    mutex p2_p3;
    mutex p3_p4;
    mutex p4_p5;
    mutex p5_p1;

    Philosopher p1(1, ref(p1_p2), ref(p5_p1));
    Philosopher p2(2, ref(p2_p3), ref(p1_p2));
    Philosopher p3(3, ref(p3_p4), ref(p2_p3));
    Philosopher p4(4, ref(p4_p5), ref(p3_p4));
    Philosopher p5(5, ref(p5_p1), ref(p4_p5));

    //Car c2("MINI JCW");

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
