#include "Philosopher.h"
// #include "utils.h" - siehe utils.h für erklärung

using namespace std;

std::recursive_mutex out_mtx;

void println() { 
    std::lock_guard<std::recursive_mutex> lg{out_mtx}; std::cout << std::endl;
}

template<typename T, typename... Rest>
void println(const T& word, const Rest&... rest) {
    std::lock_guard<std::recursive_mutex> lg{out_mtx}; std::cout << word << ' ';
    println(rest...);
}

void Philosopher::operator()(){
    while(true){

        println("Philosopher", to_string(id), "is thinking...");
        this_thread::sleep_for(1s);

        println("Philosopher", to_string(id), "attempts to get left fork");
        linke_gabel.lock();

        println("Philosopher", to_string(id), "got left fork. Now he wants the right one...");
        rechte_gabel.lock();

        println("Philosopher", to_string(id), "got right fork. Now he is eating...");
        this_thread::sleep_for(2s);
        println("Philosopher", to_string(id), "finished eating");

        linke_gabel.unlock();
        println("Philosopher", to_string(id), "released left fork");

        rechte_gabel.unlock();
        println("Philosopher", to_string(id), "released right fork");
    }
}