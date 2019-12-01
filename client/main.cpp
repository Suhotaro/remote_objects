
#include "transport.hpp"
#include "message.hpp"

#include <iostream>
#include <thread>

int main() {    
    std::cout << "Client\n";

    try {
        boost::asio::io_service io_service;

        client::Transport transport{io_service, "127.0.0.1", "5001"};

        std::thread t([&io_service](){ io_service.run(); });

        if (!transport.start()) {
            printf("ERROR: transport start\n");
            return 1;
        }

        char line[client::Message::max_body_length + 1];
        while (std::cin.getline(line, client::Message::max_body_length + 1))
        {
            client::Message msg;
            msg.body_length(std::strlen(line));
            std::memcpy(msg.body(), line, msg.body_length());
            msg.encode_header();
            transport.send(msg);
        }

        transport.stop();
        t.join();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
