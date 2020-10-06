#ifndef ACCOUNT
#define ACCOUNT

#include <iostream>
#include <thread>

class Account{
    private:
    int balance{0};

    public:
    Account();
    Account(int b);

    int get_balance();
    void deposit(int amount);
    bool withdraw(int amount);
};

#endif