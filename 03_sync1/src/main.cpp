#include "account.h"

using namespace std;

int main() {
    Account a1;
    a1.deposit(15);
    cout << a1.get_balance() << endl;
    cout << a1.withdraw(6) << endl;
    cout << a1.get_balance() << endl;
    cout << a1.withdraw(10) << endl;
    cout << a1.get_balance() << endl;
}
