#pragma once

#include <iostream>
#include <chrono>
#include <thread>

#include "timeutils.h"
class Clock{
    private:
    std::string name;
    std::chrono::time_point<std::chrono::system_clock> curr_time;

    public:
    Clock(std::string n){
        name = n;
        curr_time = std::chrono::system_clock::now();
    }

    Clock(std::string name_, int hours_, int minutes_, int seconds_){
        curr_time = set_time(curr_time, hours_, minutes_, seconds_);
        name = name_;
    }

    void operator()();

};