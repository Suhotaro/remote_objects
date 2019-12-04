#include "transport_sync.hpp"
#include "context.hpp"

namespace client {

TransportSync::TransportSync(const std::string& _ip
, const std::string& _port)
: Transport{service(), _ip, _port}
{}

Message TransportSync::send(const Message& msg) {
    try {
        Context::start();
        Transport::start();

        result = promise.get_future();
        Transport::send(msg);
        reply_msg = result.get();

        Transport::stop();
        Context::stop();

        return reply_msg;
    }
    catch (std::exception& e) {
        printf("TransportSync::send: %s\n", e.what());
    }
}

void TransportSync::on_msg_received(const Message& msg) {
    promise.set_value(msg);
}

} // namespace clients
