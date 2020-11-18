#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class Philosopher{
    private:
    int id{-1};

    std::mutex &linke_gabel;
    std::mutex &rechte_gabel;

    public:
    Philosopher(int i, std::mutex &lg, std::mutex &rg):id( i ), linke_gabel( lg ), rechte_gabel( rg ){};

    int getId() { return id; }

    void operator()();
};