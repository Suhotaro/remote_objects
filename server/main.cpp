#include "server.hpp"

#include <iostream>
#include <boost/asio.hpp>

int main() {
    std::cout << "Server\n";

    try {
        boost::asio::io_service io_service;
        std::shared_ptr<server::Server> server = std::make_shared<server::Server>(io_service);
        server->start();

        std::cout << "Server started\n";
        
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}