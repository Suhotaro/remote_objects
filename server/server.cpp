#include "server.hpp"

#include <boost/asio.hpp>

namespace server {

void Server::start() {
    acceptor.reset(new Acceptor{shared_from_this(), io_service, "5001"});
    acceptor->start();
}

} // namespace server
