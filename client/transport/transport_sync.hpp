#pragma once

#include "transport.hpp"
#include "context.hpp"

#include <future>

namespace client
{

class TransportSync : public Context, protected Transport
{
public:
    TransportSync(const std::string& ip,
        const std::string& port);
    virtual ~TransportSync() = default;
    
    virtual void send(const Message&) override;

    Message reply();

private:
    virtual void on_msg_received(const Message&) override;

    std::promise<Message> promise;
    std::future<Message> result;
    Message reply_msg;
};

} // namespace client
