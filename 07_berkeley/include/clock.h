#pragma once

#include <iostream>
#include <chrono>

class Clock{
    private:
    std::string name;
    std::chrono::system_clock::time_point sys_clock;

    public:
    Clock(std::string n){
        name = n;
        sys_clock = std::chrono::system_clock::now();
    }

};