#include "account.h"

using namespace std;

Account::Account(){
    balance = 0;
}

Account::Account(int b){
    balance = b;
}

int Account::get_balance(){
    return balance;
}

void Account::deposit(int amount){
    unique_lock<mutex> ul{m_deposit};
    int tmp{balance};
    std::this_thread::sleep_for(10ms);
    balance = tmp + amount;
    //balance = balance + amount;
}

bool Account::withdraw(int amount){
    lock_guard<mutex> guard{m};
    if( (balance - amount) >= 0 ){
        this_thread::yield();
        balance -= amount;
        return true;
    }else{
        m.unlock();
        return false;
    }
}
