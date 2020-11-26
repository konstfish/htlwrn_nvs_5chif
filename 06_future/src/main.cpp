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

void print_factors(vector<InfInt> &nc, vector<shared_future<vector<InfInt>>> &fc);
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

    app.add_option("-a, --async", io_async, "async");

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
    for(InfInt n : number_container){
        future_container.push_back(async(get_factors, n));
    }

    // call print function
    thread t_output{print_factors, ref(number_container), ref(future_container)};
    t_output.join();

    thread t_check{compare_factor, ref(number_container), ref(future_container)};
    t_check.join();
    
    //print_factors(number_container, future_container);

    return 0;
}

// IN: &nc - number vector
//     &fc - future vector
// OUT: /
void print_factors(vector<InfInt> &nc, vector<shared_future<vector<InfInt>>> &fc){
    for(size_t cnt = 0; cnt < nc.size(); cnt++){
        cout << nc.at(cnt) << ": ";
        for(InfInt n : fc.at(cnt).get()){
            cout << n << " ";
        }
        cout << endl;
    }
}

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