#include "account.h"
#include "CLI11.hpp"

using namespace std;

int main(int argc, char** argv) {
    CLI::App app("Account app");

    int balance{0};
    int deposits{5};

    app.add_option("balance", balance, "Initial balance")->required();
    app.add_option("-d,--deposits", deposits, "Count of deposits", true);
    
    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) { 
        return app.exit(e);
    }

    Account a1;
    a1.deposit(balance);

    Depositer d1(ref(a1), deposits);
    Depositer d2(ref(a1), deposits);

    thread t1{ref(d1)};
    thread t2{ref(d2)};

    t1.join();
    t2.join();

    std::this_thread::sleep_for(500ms);
    cout << a1.get_balance() << endl;

    // Punkt 6
    // Kein Großer unterschied, bis auf deklarieren der Funktionen
    // Innerhalb von account.cpp (Klasse::funktion), innerhalb header
    // ganz normal
    /*
    Account a1;

    Depositer d1(ref(a1), 10);
    Depositer d2(ref(a1), 10);

    thread t1{ref(d1)};
    thread t2{ref(d2)};

    t1.join();
    t2.join();

    std::this_thread::sleep_for(300ms);
    cout << a1.get_balance() << endl;
    */

    // Punkt 1
    /*
    Account a1;
    a1.deposit(15);
    cout << a1.get_balance() << endl;
    cout << a1.withdraw(6) << endl;
    cout << a1.get_balance() << endl;
    cout << a1.withdraw(10) << endl;
    cout << a1.get_balance() << endl;
    */

   // Punkt 2
   // Ergebnis ist wie Erwartet, einer der Threads "gewinnt" 
   // und bucht den Euro zuerst ab

   // Punkt 4
   // Beide Threads können die Abfrage starten & da sie bei Beiden True ist,
   // Buchen beide ab. Das Resultiert in einem Kontostand von -1 
   
   /*
   Account a1;
   a1.deposit(1);

    auto w1{[](Account &a1) {
        cout << "T1 - " << a1.withdraw(1) << endl;
    }};

    auto w2{[](Account &a1) {
        cout << "T2 - " << a1.withdraw(1) << endl;
    }};

   thread t1{w1, ref(a1)};
   thread t2{w2, ref(a1)};

   t1.join();
   t2.join();

   cout << "Bal: " << a1.get_balance() << endl;
   */
}
