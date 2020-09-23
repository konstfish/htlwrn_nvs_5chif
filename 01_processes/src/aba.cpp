/*
    FISCHER David

Antworten:

1.) Die ausgabe ist fast unvorhersehbar da wir keinen wirklichen
    Rechenaufwand haben.
*/

#include <iostream>
#include <unistd.h>
#include <cstdlib>

using namespace std;

int main() {
    auto pid{fork()};

    if (pid == 0) {
        // parent
        while (true) {
            cout << "A";
            cout << flush;
            sleep(1);
        }
    } else {
        // child
        while (true) {
            cout << "B";
            cout << flush;
            sleep(1);
        }
    }

    cout << "Terminated" << endl;
    return 0;
}
