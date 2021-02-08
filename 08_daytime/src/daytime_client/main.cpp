#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <asio.hpp>

#include "CLI11.hpp"

using namespace asio::ip;
using namespace std;

int main(int argc, char** argv) {
    auto console = spdlog::stdout_color_mt("console");

    spdlog::get("console")->info("Starting Daytime Client!");

    CLI::App app("Daytime Client");

    string port{"1113"};

    app.add_option("port", port, "port to connect to");

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) { 
        spdlog::get("console")->error("Error while Parsing CLI Arguments");

        return app.exit(e);
    }

    spdlog::get("console")->info("CLI Arguments successfully parsed");

    
    /*
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(5));

    t.wait();

    spdlog::get("console")->info("test!");
    */

    tcp::iostream strm{"localhost", port};

    spdlog::get("console")->info("Attempting to connect to server on port {}.", port);


    if(strm) {
        try {
            string data;
            getline(strm, data);
            cout << data << endl;
            strm.close();
        } catch(exception e) {
            spdlog::get("console")->error("Unable to recieve data from server!");
        }
    } else { 
        spdlog::get("console")->error("Could not connect to server!");
    }

    return 0;
}
