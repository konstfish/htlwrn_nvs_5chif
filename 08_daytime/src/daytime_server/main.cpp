#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

using namespace std;

int main() {
    auto console = spdlog::stdout_color_mt("console");
    
    spdlog::get("console")->info("test!");

    return 0;
}
