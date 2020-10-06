#ifndef ACCOUNT
#define ACCOUNT

#include <iostream>
#include <thread>
#include <mutex>

class Account{
    private:
    int balance{0};
    std::mutex m;
    std::mutex m_deposit;

    public:
    Account();
    Account(int b);

    int get_balance();
    void deposit(int amount);
    bool withdraw(int amount);
};

class Depositer{
    private:
    Account &acc;

    public:
    Depositer(Account &a):acc(a){};

    void operator()(){
        int i = 0;
        while ( i < 5 ){
            acc.deposit(1);
            i += 1;
        }
        std::cout << acc.get_balance() << std::endl;
    }
};

#endif