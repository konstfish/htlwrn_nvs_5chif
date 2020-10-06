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
    int deposits;

    public:
    Depositer(Account &a, int dep):acc(a), deposits(dep){};

    void operator()(){
        int i = 0;
        if(deposits > 0){
            while ( i < deposits ){
                acc.deposit(1);
                i += 1;
            }
        }else{
            while ( i > deposits ){
                acc.withdraw(1);
                i -= 1;
            }
        }
    }
};

#endif