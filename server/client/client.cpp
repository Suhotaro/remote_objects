#include "client.hpp"
#include "photo_editor.hpp"
#include "stream.hpp"
#include "server.hpp"
#include "util.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>
#include <string>

namespace server {

Client::Client(std::shared_ptr<Acceptor> _acceptor,
    std::shared_ptr<Server> _server,
    boost::asio::io_service& _io_service)
: Transport(_acceptor, _io_service)
, server{_server}
{}

void Client::on_msg_received(const Message& msg) {
    boost::property_tree::ptree msg_tree;
    std::istringstream is (msg.body());
    boost::property_tree::read_json (is, msg_tree);

    if (msg_tree.get<std::string>("methode") == "create") {
        boost::property_tree::ptree reply_object;
        boost::property_tree::ptree reply_arguments;    
        reply_object.put("methode", "create");

        // TODO: fix double create
        if (msg_tree.get<std::string>("object") == "PhotoEditor") {
            auto photo_editor = std::dynamic_pointer_cast<PhotoEditor>(server->objects_repository()->make_photo_editor());
            reply_arguments.put("uuid", photo_editor->id());
            reply_object.put("object", "PhotoEditor");
            reply_object.add_child("aruments", reply_arguments);
        } else if (msg_tree.get<std::string>("object") == "Stream") {
            auto photo_editor = std::dynamic_pointer_cast<PhotoEditor>(server->objects_repository()->make_photo_editor());
            reply_arguments.put("uuid", photo_editor->id());
            reply_object.put("object", "Stream");
            reply_object.add_child("aruments", reply_arguments);
        }

        send(to_msg(to_string(reply_object)));
        return;
    }

    if (msg_tree.get<std::string>("object") == "PhotoEditor") {
        auto photo_editor = std::dynamic_pointer_cast<PhotoEditor>(server->objects_repository()->find(msg_tree.get<int>("uuid")));
        photo_editor->on_msg_received(shared_from_this(), msg);
    } else if (msg_tree.get<std::string>("object") == "Stream") {
        auto stream = std::dynamic_pointer_cast<Stream>(server->objects_repository()->find(msg_tree.get<int>("uuid")));
        stream->on_msg_received(shared_from_this(), msg);
    }
}

} // namespace server

