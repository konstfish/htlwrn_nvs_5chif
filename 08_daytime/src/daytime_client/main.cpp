#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <asio.hpp>

#include "CLI11.hpp"

using namespace asio::ip;
using namespace std;

int main(int argc, char** argv) {
    CLI::App app("Daytime Client");

    string port{"1113"};

    app.add_option("port", port, "port to connect to") -> required();

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) { 
        return app.exit(e);
    }
    auto console = spdlog::stdout_color_mt("console");
    
    /*
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(5));

    t.wait();

    spdlog::get("console")->info("test!");
    */

    tcp::iostream strm{"localhost", port};

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
