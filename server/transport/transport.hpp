#pragma once

#include "message.hpp"
#include <deque>
#include <list>

#include <boost/asio.hpp>

namespace server
{

class Acceptor;

class Transport : public std::enable_shared_from_this<Transport> {
using message_queue = std::deque<Message>;

public:
    Transport(std::shared_ptr<Acceptor>,
        boost::asio::io_service& io_service);

    bool start();
    void send(const Message& msg);

    virtual void on_msg_received(const Message& msg) = 0;

    boost::asio::ip::tcp::socket& socket_get();

private:
    void do_read_header();
    void do_read_body();
    void do_write();

    boost::asio::ip::tcp::socket socket;
    Message read_msg;
    message_queue write_msgs;
    std::shared_ptr<Acceptor> acceptor;
};

using Transports = std::list<std::shared_ptr<Transport>>;

} // namespace server
