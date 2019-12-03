#pragma once

#include "acceptor.hpp"
#include "avl_tree.hpp"

#include <memory>

namespace server {

class Acceptor;
class Object;

class Server : public std::enable_shared_from_this<Server>  {
public:
    Server(boost::asio::io_service& _io_service);
    void start();

    std::shared_ptr<AvlTree> objects_repository() { return tree; }

private:
    std::unique_ptr<Acceptor> acceptor;

    boost::asio::io_service& io_service;
    std::shared_ptr<AvlTree> tree;
};

} // namespace server
