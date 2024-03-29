#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>

#include "timeutils.h"
class Clock{
    private:
    std::string name;
    std::chrono::time_point<std::chrono::system_clock> curr_time;

    int second_step;

    bool monoton{false};
    int monoton_delay{0};

    public:
    Clock(){};

    Clock(std::string name_){
        name = name_;
        curr_time = std::chrono::system_clock::now();
    }

    Clock(std::string name_, int hours_, int minutes_, int seconds_){
        curr_time = ::set_time(curr_time, hours_, minutes_, seconds_);
        name = name_;
    }

    Clock(std::string name_, int hours_, int minutes_, int seconds_, int step){
        curr_time = ::set_time(curr_time, hours_, minutes_, seconds_);
        name = name_;
        second_step = step;
    }

    void operator()();

    void set_time(int hours, int minutes, int seconds);
    std::tuple<int, int, int> get_time();

    long to_time();
    void from_time(long time);

    void set_time_monoton(bool toggle){
        monoton = toggle;
    }

    void debug_out();
};