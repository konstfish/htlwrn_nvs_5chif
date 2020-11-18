#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class Philosopher{
    private:
    int id{-1};

    std::timed_mutex &linke_gabel;
    std::timed_mutex &rechte_gabel;

    int deadlock_prevention{1};
    int livelock{0};

    public:
    Philosopher(int i, std::timed_mutex &lg, std::timed_mutex &rg, int dp, int ll):id( i ), linke_gabel( lg ), rechte_gabel( rg ), deadlock_prevention( dp ), livelock( ll ){};

    int getId() { return id; }

    void operator()();
};