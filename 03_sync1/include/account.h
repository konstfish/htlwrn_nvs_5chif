#ifndef ACCOUNT
#define ACCOUNT

#include <iostream>
#include <thread>
#include <mutex>

class Account{
    private:
    int balance{0};
    std::mutex m;

    public:
    Account();
    Account(int b);

    int get_balance();
    void deposit(int amount);
    bool withdraw(int amount);
};

#endif