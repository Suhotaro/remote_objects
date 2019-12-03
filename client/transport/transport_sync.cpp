#include "transport_sync.hpp"

namespace client {

TransportSync::TransportSync(boost::asio::io_service& _io_service
, const std::string& _ip
, const std::string& _port)
: Transport{_io_service, _ip, _port}
{}

void TransportSync::send(const Message& msg) {
    try {
        io_service_thread = std::thread{[this](){ io_service.run(); }};

        if (!Transport::start()) {
            printf("ERROR: TransportSync start\n");
            exit(1);
        }
        result = promise.get_future();
        Transport::send(msg);

        printf("CLIENT: wait result\n");
        reply_msg = result.get();

        Transport::stop();
        io_service_thread.join();
    }
    catch (std::exception& e) {
        printf("TransportSync::send: %s\n", e.what());
    }
}

Message TransportSync::reply() {
    return reply_msg;
}

void TransportSync::on_msg_received(const Message& msg) {
    printf("CLIENT: receive result\n");
    promise.set_value(msg);
}

} // namespace clients
