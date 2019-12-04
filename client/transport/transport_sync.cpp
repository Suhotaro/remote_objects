#include "transport_sync.hpp"
#include "context.hpp"

namespace client {

TransportSync::TransportSync(boost::asio::io_service& _io_service
, const std::string& _ip
, const std::string& _port)
: Transport{_io_service, _ip, _port}
{}

void TransportSync::send(const Message& msg) {
    try {
        io_service_thread = std::thread{[this]() {
            boost::asio::io_service::work work(io_service);
            io_service.run();
        }};

        if (!Transport::start()) {
            printf("ERROR: TransportSync start\n");
            exit(1);
        }
        result = promise.get_future();
        Transport::send(msg);

        printf("CLIENT: wait result\n");
        reply_msg = result.get();
        printf("CLIENT: continue\n");

        Transport::stop();
        io_service.stop();
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
    promise.set_value(msg);
}

} // namespace clients
