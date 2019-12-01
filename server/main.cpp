#include <iostream>

#include "acceptor.hpp"

int main() {
    std::cout << "Server\n";

    try{
        boost::asio::io_service io_service;
        auto acceptor = std::make_shared<server::Acceptor>(io_service, "5001");
        acceptor->start();

        std::cout << "Server started\n";

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }


    return 0;
}