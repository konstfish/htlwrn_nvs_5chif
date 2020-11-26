#include <iostream>
#include "CLI11.hpp"

//#define LONG_LONG_MAX LLONG_MAX;
//#define LONG_LONG_MIN LLONG_MIN;
//#define ULONG_LONG_MAX ULLONG_MAX;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#pragma GCC diagnostic ignored "-Wsign-compare"
#include "InfInt.h"
#pragma GCC diagnostic pop
using namespace std;

int main(int argc, char** argv) {
    CLI::App app("Factor numbers");

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) { 
        return app.exit(e);
    }

    return 0;
}
