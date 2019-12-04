#pragma once

#include "transport.hpp"

#include <boost/property_tree/ptree.hpp>

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
    void create_new_object(const boost::property_tree::ptree& json_tree);

    std::shared_ptr<Server> server;
};

} // namespace server
