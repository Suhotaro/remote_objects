#pragma once

#include "message.hpp"

#include <boost/asio.hpp>

namespace client
{

class Transport
{
public:
    Transport(boost::asio::io_service&,
            const std::string& ip,
            const std::string& port);

    bool start();
    void stop();

    void send(const Message& data);

private:
    void do_read_header();
    void do_read_body();

    std::string ip;
    std::string port;

    boost::asio::io_service& io_service;
    boost::asio::ip::tcp::socket socket;

    Message read_msg;
};

} // namespace client
