
#include "client.hpp"
#include "message.hpp"
#include "photo_editor.hpp"

#include <iostream>
#include <thread>

int main() {    
    std::cout << "Client\n";

    client::Client client;
    std::shared_ptr<client::PhotoEditor> photo_editor = client.make_photo_editor();
    

/*
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
  
        }

        transport.stop();
        t.join();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
*/
    return 0;
}
