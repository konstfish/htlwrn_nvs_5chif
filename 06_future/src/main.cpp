#include <iostream>
#include <vector>
#include <future>

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

    // output

    vector<future<vector<InfInt>>> future_container;

    future<vector<InfInt>> futuret;



    for(InfInt n : number_container){
        
        // vector<InfInt> asdf = get_factors(n);

        future_container.push_back(async(get_factors, n));


        //for(InfInt fac : asdf){
        //    cout << fac << " ";
        //}

        //futuret = get_factors(n);

        //cout << endl;
    }

    for(size_t cnt = 0; cnt < future_container.size(); cnt++){
        cout << number_container.at(cnt) << ": ";
        for(InfInt n : future_container.at(cnt).get()){
            cout << n << " ";
        }
        cout << endl;
    }


    return 0;
}
