#pragma once

#include <boost/asio.hpp>

#include "transport.hpp"

namespace server
{

class Acceptor : public std::enable_shared_from_this<Acceptor>
{
public:
    Acceptor(boost::asio::io_service&,
            const std::string port);

    bool start();
    void stop();

    void register_transport(std::shared_ptr<Transport>);
    void unregister_transport(std::shared_ptr<Transport>);

private:
    void do_accept();

    boost::asio::io_service& io_service;
    boost::asio::ip::tcp::socket socket;
    boost::asio::ip::tcp::acceptor acceptor;

    Transports transports;
};

} // namespace server
