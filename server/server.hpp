#pragma once

//#include <boost/intrusive/avltree.hpp>

#include "acceptor.hpp"

#include <memory>


namespace server {

class Acceptor;

class Server : public std::enable_shared_from_this<Server>  {
public:
    Server(boost::asio::io_service& _io_service) : io_service(_io_service) {}
    void start();

private:
    std::unique_ptr<Acceptor> acceptor;
    int uuid = 0;

    boost::asio::io_service& io_service;

    //boost::intrusive::avltree<std::shared_ptr<Object>> avltree;
};

} // namespace server
