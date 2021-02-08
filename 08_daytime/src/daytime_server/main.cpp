#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <asio.hpp>

#include "CLI11.hpp"

#include <iomanip>
#include <ctime>

using namespace asio::ip;
using namespace std;

int main(int argc, char** argv) {
    auto console = spdlog::stdout_color_mt("console");

    spdlog::get("console")->info("Starting Daytime Server!");

    CLI::App app("Daytime Server");

    int port{1113};

    app.add_option("port", port, "server port");

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) { 
        spdlog::get("console")->error("Error while Parsing CLI Arguments");

        return app.exit(e);
    }

    spdlog::get("console")->info("CLI Arguments successfully parsed");

    spdlog::get("console")->info("Starting server on port {}.", port);

    asio::io_context ctx;
    tcp::endpoint ep{tcp::v4(), 1113}; 
    tcp::acceptor acceptor{ctx, ep};
    tcp::socket sock{ctx};
    //acceptor.accept(sock);
    //tcp::iostream strm{std::move(sock)};

    while(true){
        spdlog::get("console")->info("Waiting for connection");

        acceptor.accept(sock);
        tcp::iostream strm{std::move(sock)};

        spdlog::get("console")->info("Connection established");

        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        strm << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
        strm.close();

        spdlog::get("console")->info("Connection finished processing");
    }

    return 0;
}
