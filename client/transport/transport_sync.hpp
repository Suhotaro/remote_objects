#pragma once

#include "transport.hpp"
#include <future>

namespace client
{

class TransportSync : protected Transport
{
public:
    TransportSync(boost::asio::io_service& io_service,
        const std::string& ip,
        const std::string& port);
    virtual ~TransportSync() = default;
    
    virtual void send(const Message&) override;

    Message reply();

private:
    virtual void on_msg_received(const Message&) override;

    std::promise<Message> promise;
    std::future<Message> result;
    Message reply_msg;

    std::thread io_service_thread;
};

} // namespace client
