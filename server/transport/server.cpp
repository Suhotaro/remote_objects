#include "server.hpp"

#include <boost/asio.hpp>

namespace server {

Server::Server(boost::asio::io_service& _io_service)
: io_service(_io_service)
, tree{std::make_shared<AvlTree>()}
{}

void Server::start() {
    acceptor.reset(new Acceptor{shared_from_this(), io_service, "5001"});
    acceptor->start();
}

} // namespace server
