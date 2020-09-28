#include <iostream>
#include <thread>
#include <random>
#include <iomanip>
#include <sstream>

using namespace std;

void mini_jcw(double& total_time);

class Car{
    public:
    string name;
    double total_time{0};

    Car(string n){
        name = n;
    }

    void operator()(){
        int round = 0;
        string tmp;
        ostringstream buf;

        random_device rd;
        std::mt19937 gen{rd()}; std::uniform_real_distribution<> dis{1, 10};
        double seconds;

        while (round < 10) {
            seconds = dis(gen);
            this_thread::sleep_for(chrono::milliseconds{(int)(seconds * 1000)});
            round += 1;
            total_time += seconds;

            // tmp = to_string(round) + " " + name + " " + to_string(dis(gen)) + "s\n";

            buf << setprecision(3);
            buf << round << " " << name << " " << seconds << "s\n";
            tmp = buf.str();
            buf.str("");

            cout << tmp;
        }
        cout << total_time << endl;
    }

    double get_total_time(){
        return total_time;
    }
};

int main() {

    Car c1("MINI Cooper S");
    //Car c2("MINI JCW");

    thread t1{c1};

    double total_time{0};
    thread t2{mini_jcw, ref(total_time)};
    
    t1.join();
    t2.join();

    cout << "MINI Cooper S: " << c1.get_total_time() << "s" << endl;
    cout << "MINI JCW: " << total_time << "s" << endl;
    //thread t2{c2};
}

// wusste bis zu diesem commit nicht dass wir diese funktion weiterführen müssen, ups!
void mini_jcw(double& total_time){
    int round = 0;
    string tmp;
    ostringstream buf;

    random_device rd;
    std::mt19937 gen{rd()}; std::uniform_real_distribution<> dis{1, 10};
    double seconds;

    while (round < 10) {
        seconds = dis(gen);
        this_thread::sleep_for(chrono::milliseconds{(int)(seconds * 1000)});
        round += 1;
        total_time += seconds;

        // tmp = to_string(round) + " " + name + " " + to_string(dis(gen)) + "s\n";

        buf << setprecision(3);
        buf << round << " " << "MINI JCW" << " " << seconds << "s\n";
        tmp = buf.str();
        buf.str("");

        cout << tmp;
    }
}