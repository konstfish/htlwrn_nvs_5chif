#include <iostream>
#include "work_queue.h"

using namespace std;

int main() {
    WorkPacket p(1);
    WorkPacket p2(2);
    WorkPacket p3(3);

    // cout << p.getId() << endl;

    WorkQueue wq1;
    wq1.push(p3);
    wq1.push(p);
    wq1.push(p2);
    cout << wq1.pop().getId() << endl;
    cout << wq1.pop().getId() << endl;
    cout << wq1.pop().getId() << endl;
    cout << wq1.pop().getId() << endl;
    cout << wq1.pop().getId() << endl;

    return 0;
}
