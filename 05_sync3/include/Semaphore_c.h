#pragma once

#include <iostream>
#include <mutex>
#include <atomic>
#include <condition_variable>

class Semaphore_c{
    const int MAX = 4;
    std::atomic<int> cnt;

    std::mutex mtx;
    std::condition_variable not_empty;
    std::condition_variable not_full;

    public:
        Semaphore_c(){ cnt.store(0); }

        void acquire();
        void release();
        int available_permits();
};
