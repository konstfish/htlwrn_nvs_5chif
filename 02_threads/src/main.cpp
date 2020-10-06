#include <iostream>
#include <thread>
#include <random>
#include <iomanip>
#include <sstream>

using namespace std;

void mini_jcw(double& total_time, int rounds);
void help();
void error(string msg="");

class Car{
    public:
    string name;
    int rounds;
    double total_time{0};

    Car(string n, int r){
        name = n;
        rounds = r;
    }

    void operator()(){
        int round = 0;
        string tmp;
        ostringstream buf;

        random_device rd;
        std::mt19937 gen{rd()}; std::uniform_real_distribution<> dis{1, 10};
        double seconds;

        while (round < rounds) {
            seconds = dis(gen);
            this_thread::sleep_for(chrono::milliseconds{(int)(seconds * 1000)});
            round += 1;
            total_time += seconds;

            buf << setprecision(3);
            buf << round << " " << name << " " << seconds << "s\n";
            tmp = buf.str();
            buf.str("");

            cout << tmp;
        }
    }

    double get_total_time(){
        return total_time;
    }
};

int main(int argc, char* argv[]) {
    int rounds = 10;
    if(argc > 1){
        if(string(argv[1]) == "-h" or string(argv[1]) == "--help"){
            help();
            return 0;
        }else{
            try{
                std::size_t size;
                rounds = stoi(argv[1], &size);
                if(size != strlen(argv[1])){
                    throw exception();
                }

                if(0 >= rounds or rounds > 16){
                    error("Out of range (1 <= LAP'S < 16): " + to_string(rounds));
                    return 1;
                }
            }catch(...){
                error("Could not convert: " + string(argv[1]));
                return 1;
            }
        }
    }

    Car c1("MINI Cooper S", rounds);
    //Car c2("MINI JCW");

    thread t1{ref(c1)};

    double total_time{0};
    thread t2{mini_jcw, ref(total_time), rounds};
    
    t1.join();
    t2.join();

    //cout << "MINI Cooper S: " << c1.get_total_time() << "s" << endl;
    //cout << "MINI JCW: " << total_time << "s" << endl;

    if(c1.get_total_time() > total_time){
        cout << "Sieger ist: " << "MINI JCW mit " << total_time << "s" << endl;
        cout << "Verlierer ist: " << "MINI Cooper S mit " << c1.get_total_time() << "s" << endl;
    }else{
        cout << "Sieger ist: " << "MINI Cooper S mit " << c1.get_total_time() << "s" << endl;
        cout << "Verlierer ist: " << "MINI JCW mit " << total_time << "s" << endl;
    }
    return 0;
}

void help(){
    cout << "Usage: contest [-h | --help | LAPS]" << endl;
}

void error(string msg){
    cout << msg << endl << "Run with --help for more information" << endl;
}

void mini_jcw(double& total_time, int rounds){
    int round = 0;
    string tmp;
    ostringstream buf;

    random_device rd;
    std::mt19937 gen{rd()}; std::uniform_real_distribution<> dis{1, 10};
    double seconds;

    while (round < rounds) {
        seconds = dis(gen);
        this_thread::sleep_for(chrono::milliseconds{(int)(seconds * 1000)});
        round += 1;
        total_time += seconds;

        buf << setprecision(3);
        buf << round << " " << "MINI JCW" << " " << seconds << "s\n";
        tmp = buf.str();
        buf.str("");

        cout << tmp;
    }
}