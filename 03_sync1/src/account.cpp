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
    balance += amount;
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