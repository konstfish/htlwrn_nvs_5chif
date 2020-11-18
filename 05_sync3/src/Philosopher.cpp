#include "Philosopher.h"
#include "Semaphore_c.h"
// #include "utils.h" - siehe utils.h für erklärung

using namespace std;

std::recursive_mutex out_mtx;
Semaphore_c sem;

void println() { 
    std::lock_guard<std::recursive_mutex> lg{out_mtx}; std::cout << std::endl;
}

template<typename T, typename... Rest>
void println(const T& word, const Rest&... rest) {
    std::lock_guard<std::recursive_mutex> lg{out_mtx}; std::cout << word << ' ';
    println(rest...);
}

void Philosopher::operator()(){
    bool able_to_think{true}; // damit sie nicht denken, wenn sie nichts gegessen haben (livelock)
    while(true){
        
        if(able_to_think){
            println("Philosopher", to_string(id), "is thinking...");
            able_to_think = false;
            this_thread::sleep_for(1s);
        }

        println("Philosopher", to_string(id), "attempts to get left fork");

        if(deadlock_prevention){
            if(sem.available_permits() <= 2){
                println("Currently", to_string(sem.available_permits()), "left forks available");
            }
            sem.acquire();
        }
        linke_gabel.lock();

        this_thread::sleep_for(5s);

        println("Philosopher", to_string(id), "got left fork. Now he wants the right one...");
        
        if(!livelock){
            rechte_gabel.lock();
        }else{
            if(!rechte_gabel.try_lock_for(std::chrono::seconds(3))){
                this_thread::sleep_for(100ms);
                println("Philosopher", to_string(id), "released left fork due to timeout getting the right one!");
                linke_gabel.unlock();
                if(deadlock_prevention){
                    sem.release();
                }
                continue;
            }
        }

        println("Philosopher", to_string(id), "got right fork. Now he is eating...");
        this_thread::sleep_for(2s);
        println("Philosopher", to_string(id), "finished eating");

        linke_gabel.unlock();
        if(deadlock_prevention){
            sem.release();
        }
        println("Philosopher", to_string(id), "released left fork");

        rechte_gabel.unlock();
        println("Philosopher", to_string(id), "released right fork");

        able_to_think = true;
    }
    // Beide Optionen: (livelock/deadlock) Es funktioniert da das Semaphore max. 4 Gabeln verteilt
}