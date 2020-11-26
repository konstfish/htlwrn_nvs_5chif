#include <iostream>
#include <vector>
#include <future>
#include <thread>

#include "CLI11.hpp"
#include "calc_factors.h"

//#define LONG_LONG_MAX LLONG_MAX;
//#define LONG_LONG_MIN LLONG_MIN;
//#define ULONG_LONG_MAX ULLONG_MAX;
// musste meine infint.h modifizieren

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#pragma GCC diagnostic ignored "-Wsign-compare"
#include "InfInt.h"
#pragma GCC diagnostic pop
using namespace std;

//std::__1::chrono::system_clock::time_point start;

void print_factors(vector<InfInt> &nc, vector<shared_future<vector<InfInt>>> &fc, std::__1::chrono::system_clock::time_point start);
void compare_factor(vector<InfInt> &nc, vector<shared_future<vector<InfInt>>> &fc);

int main(int argc, char** argv) {
    CLI::App app("Factor numbers");

    vector<InfInt> number_container;
    vector<string> string_number_container;
    bool io_async{false};

    app.add_option("number", string_number_container, "numbers to factor") -> required() 
    -> check([](const std::string &str) {
            auto found = str.find_first_not_of("0123456789");

            if(found==std::string::npos) {
                return std::string();
            }
            else {
                return std::string(str + " contains not numeric character");
            }
        }
        );

    app.add_flag("-a, --async", io_async, "async");

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) { 
        return app.exit(e);
    }

    // convert to InfInt
    InfInt tmp;

    for(string sn : string_number_container){
        tmp = sn;
        number_container.push_back(tmp);
    }

    // create future vector
    vector<shared_future<vector<InfInt>>> future_container;

    // fill future vector
    auto start = chrono::system_clock::now();
    for(InfInt n : number_container){
        if(!io_async){
            future_container.push_back(async(get_factors, n));
        }else{
            future_container.push_back(async(launch::async, get_factors, n));
        }
    }

    // call print function
    thread t_output{print_factors, ref(number_container), ref(future_container), start};
    t_output.join();

    thread t_check{compare_factor, ref(number_container), ref(future_container)};
    t_check.join();
    
    //print_factors(number_container, future_container);

    /*
    
    Hintereinander Callen: Es wird immer schneller, bis er ein limit erreicht. Vermutlich
    da die Werte noch im Speicher vorliegen (?)

    */

    return 0;
}

// IN: &nc - number vector
//     &fc - future vector
// OUT: /
void print_factors(vector<InfInt> &nc, vector<shared_future<vector<InfInt>>> &fc, std::__1::chrono::system_clock::time_point start){
    for(size_t cnt = 0; cnt < nc.size(); cnt++){
        cout << nc.at(cnt) << ": ";
        for(InfInt n : fc.at(cnt).get()){
            cout << n << " ";
        }
        cout << endl;
    }
    auto duration = chrono::duration_cast<chrono::milliseconds> (std::chrono::system_clock::now() - start);
    cout << "Time elapsed used for factoring: " << duration.count() << "ms" << endl;
}

// IN: &nc - number vector
//     &fc - future vector
// OUT: /
void compare_factor(vector<InfInt> &nc, vector<shared_future<vector<InfInt>>> &fc){
    InfInt tmp{0};
    for(size_t cnt = 0; cnt < nc.size(); cnt++){
        for(InfInt n : fc.at(cnt).get()){
            if(tmp == 0){
                tmp = n;
            }else{
                tmp *= n;
            }
        }
        if(tmp != nc.at(cnt)){
            cerr << "Fehler: Faktorielle nicht gleich ursprünglicher Nummer" << endl << nc.at(cnt) << " != " << tmp;
        }
        tmp = 0;
    }
}