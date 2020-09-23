/*
    FISCHER David

Notes:
ps -alx | grep aba | grep -v Chrome | grep -v grep
ps -alx | grep charout | grep -v Chrome | grep -v grep

Antworten:
1.) Die ausgabe ist fast unvorhersehbar da wir keinen wirklichen
    Rechenaufwand haben.

6.) Ich bekomme es beim besten willen nicht zusammen einen Zombie
    zu erzeugen. Könnte an macOS liegen, bin mir aber nicht sicher.
    Jedenfalls sollte ein Zombie entstehen da nie waitpid() aufgerufen
    wird.

    Um zu überprüfen, ob ein Prozess zum Zombie geworden ist, reicht der 
    command 'ps <PID des Prozesses>' also zum Beispiel `ps 123`

7.) Output:
    Child: 17048
    BAABABABABABA
    Status: 9 <------ Status ist 9, da das SIGKILL Signal gesendet wird.

*/

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <signal.h>
#include <cerrno>

using namespace std;

int main() {
    auto pid{fork()};
    std::chrono::milliseconds sleeptime(500);

    if (pid == 0) {
        // child
        try{
            execl("./charoutdf", "charout", "A", nullptr);
        }catch(...){
            cerr << strerror(errno) << endl;
        }
    } else {
        // parent
        int iterations = 0;
        cout << "Child: " << pid << endl;

        while (true) {
            iterations += 1;
            cout << "B";
            cout << flush;
            this_thread::sleep_for(sleeptime);
            if(iterations == 6){
                kill(pid, SIGKILL);
                int status;
                waitpid(pid, &status, 0);
                cout << endl << "Status: " << status;
                exit(0);
            }
        }
    }

    cout << "Terminated" << endl;
    return 0;
}
