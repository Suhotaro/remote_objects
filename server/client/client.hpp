#pragma once

#include "transport.hpp"
#include <memory>

namespace server {

class Server;

class Client final : public Transport {
public:
    Client(std::shared_ptr<Acceptor>,
        std::shared_ptr<Server>,
        boost::asio::io_service& io_service);

    virtual void on_msg_received(const Message& msg) override;

private:
    std::shared_ptr<Server> server;
};

} // namespace server
