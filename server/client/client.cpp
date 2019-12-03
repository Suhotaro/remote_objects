#include "client.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>

namespace server {

Client::Client(std::shared_ptr<Acceptor> _acceptor,
    boost::asio::io_service& _io_service)
: Transport(_acceptor, _io_service) {
}

void Client::on_msg_received(const Message& msg) {
    boost::property_tree::ptree reply_tree;
    std::istringstream is (msg.body());
    boost::property_tree::read_json (is, reply_tree);

    send(msg);
}

} // namespace server

