#pragma once

#include "transport.hpp"

namespace server {

class Client final : public Transport {
public:
    Client(std::shared_ptr<Acceptor>, boost::asio::io_service& io_service);

    virtual void on_msg_received(const Message& msg) override;
};

} // namespace server
