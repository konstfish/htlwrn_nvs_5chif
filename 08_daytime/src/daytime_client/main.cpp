#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <asio.hpp>

using namespace std;

int main() {
    auto console = spdlog::stdout_color_mt("console");
    
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(5));

    t.wait();

    spdlog::get("console")->info("test!");

    return 0;
}
