#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <asio.hpp>

using namespace asio::ip;
using namespace std;

int main() {
    auto console = spdlog::stdout_color_mt("console");
    
    /*
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(5));

    t.wait();

    spdlog::get("console")->info("test!");
    */

    tcp::iostream strm{"localhost", "1113"};



    if(strm) {
        string data;
        getline(strm, data);
        cout << data << endl;
        strm.close();
    } else { 
        cout << "no connection" << endl; 
    }

    return 0;
}
