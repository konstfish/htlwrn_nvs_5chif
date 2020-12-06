#pragma once

#include <iostream>

#include "clock.h"

class TimeSlave{
    private:

    std::string name;
    Clock c;

    public:

    TimeSlave(std::string rn):name( rn ){};

    void operator()();
}