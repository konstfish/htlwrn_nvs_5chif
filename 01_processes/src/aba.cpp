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
    auto pid1{fork()};
    std::chrono::milliseconds sleeptime(500);

    const char* aba_letter_a{getenv("ABA_LETTER_A")}; 
    const char* aba_letter_b{getenv("ABA_LETTER_B")};

    if(aba_letter_a){
        cout << aba_letter_a << endl;
    }else{
        aba_letter_a = "A";
    }

    if(aba_letter_b){
        cout << aba_letter_b << endl;
    }else{
        aba_letter_b = "B";
    }

    if (pid1 == 0) {
        // child1
        int status = execl("./charout", "charout", aba_letter_a, nullptr);
        if(status == -1) {
            cerr << strerror(errno) << endl;
        }
    } else {
        auto pid2{fork()};

        if(pid2 == 0) {
            // child2
            int status = execl("./charout", "charout", aba_letter_b, nullptr);
            if(status == -1) {
                cerr << strerror(errno) << endl;
            }
        } else {
            cout << "Child1: " << pid1 << endl;
            cout << "Child2: " << pid2 << endl;
            int iterations = 0;
            while (true) {
                iterations += 1;
                this_thread::sleep_for(sleeptime);
                if(iterations == 6){
                    kill(pid1, SIGKILL);
                    kill(pid2, SIGKILL);
                    int status1;
                    waitpid(pid1, &status1, 0);
                    int status2;
                    waitpid(pid2, &status2, 0);
                    cout << endl << "Status1: " << status1;
                    cout << endl << "Status2: " << status2 << endl;
                    exit(0);
                }
            }
        }
    }

    cout << "Terminated" << endl;
    return 0;

/*
    if(pid1) {
        // parent
        if(pid2) {
            // parent
            cout << "Child1: " << pid1 << endl;
            cout << "Child2: " << pid2 << endl;
            int iterations = 0;
            while (true) {
                iterations += 1;
                this_thread::sleep_for(sleeptime);
                if(iterations == 6){
                    kill(pid1, SIGKILL);
                    int status;
                    waitpid(pid1, &status, 0);
                    cout << endl << "Status: " << status;
                    exit(0);
                }
            }
        }
        else {
            // child2
            try{
                execl("./charout", "charout", "A", nullptr);
            }catch(...){
                cerr << strerror(errno) << endl;
            }
        }
    } else {
        // child 2
        try{
            execl("./charout", "charout", "B", nullptr);
        }catch(...){
            cerr << strerror(errno) << endl;
        }
    }

    if (pid1 == 0) {
        // child
        try{
            execl("./charoutdf", "charout", "A", nullptr);
        }catch(...){
            cerr << strerror(errno) << endl;
        }
    } else {
        // parent
        int iterations = 0;
        cout << "Child: " << pid1 << endl;

        while (true) {
            iterations += 1;
            this_thread::sleep_for(sleeptime);
            if(iterations == 6){
                kill(pid1, SIGKILL);
                int status;
                waitpid(pid1, &status, 0);
                cout << endl << "Status: " << status;
                exit(0);
            }
        }
    }
*/
}
