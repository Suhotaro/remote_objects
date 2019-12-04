#include "transport_sync.hpp"
#include "context.hpp"

namespace client {

TransportSync::TransportSync(const std::string& _ip
, const std::string& _port)
: Transport{service(), _ip, _port}
{}

void TransportSync::send(const Message& msg) {
    try {
        Context::start();

        if (!Transport::start()) {
            printf("ERROR: TransportSync start\n");
            exit(1);
        }
        result = promise.get_future();
        Transport::send(msg);
        reply_msg = result.get();

        Transport::stop();
        Context::stop();
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
