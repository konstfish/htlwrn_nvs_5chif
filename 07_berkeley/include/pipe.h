#ifndef PIPE_H
#define PIPE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class Pipe {
    std::queue<T> backend;
    std::mutex mtx;
    std::condition_variable not_empty;
    bool closed{false};

    long latency{0};
  public:
    Pipe& operator<<(T value) {
        // here we go!
        std::unique_lock<std::mutex> ul{mtx};
        not_empty.wait(ul, [this](){return !closed;});

        if(!latency){
            std::this_thread::sleep_for(std::chrono::seconds(latency));
        }

        backend.push(value);

        not_empty.notify_one();

        return *this;
    }
    
    Pipe& operator>>(T& value) {
        // here we go!
        std::unique_lock<std::mutex> ul{mtx};
        not_empty.wait(ul, [this](){return (backend.size() > 0);});

        if(!latency){
            std::this_thread::sleep_for(std::chrono::seconds(latency));
        }

        value = backend.front();
        backend.pop();

        return *this;
    }

    void close() {
        closed = true;
    }
    
    explicit operator bool() {
        return closed;
    }

    void set_latency(long lat){
        latency = lat;
    }
};
#endif
