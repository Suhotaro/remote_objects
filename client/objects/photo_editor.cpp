#include "photo_editor.hpp"
#include "transport_sync.hpp"

#include <thread>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>

// todo rm
#include <iostream>

namespace client {
    
static std::string to_string(const boost::property_tree::ptree& tree)  {
    std::ostringstream oss;
    boost::property_tree::write_json(oss, tree, false);
    return oss.str();
}

void PhotoEditor::create(int uuid) {
    boost::property_tree::ptree object;
    boost::property_tree::ptree arguments;

    object.put("object", "PhotoEditor");
    object.put("methode", "create");
    arguments.put("uuid", uuid);
    object.add_child("arguments", arguments);

    Message reply = send(to_string(object));

    boost::property_tree::ptree reply_tree;
    std::istringstream is (reply.body());
    boost::property_tree::read_json (is, reply_tree);

    uuid = reply_tree.get<int>("arguments.uuid");
    printf("PhotoEditor uuid %d\n", uuid);
}

void PhotoEditor::upload(const std::string& image) {
    boost::property_tree::ptree object;
    boost::property_tree::ptree arguments;

    object.put("object", "PhotoEditor");
    object.put("methode", "upload");
    arguments.put("uuid", uuid);
    arguments.put("image", image);
    object.add_child("arguments", arguments);

    send(to_string(object));
}

void PhotoEditor::rotate(int degree) {
    boost::property_tree::ptree object;
    boost::property_tree::ptree arguments;

    object.put("object", "PhotoEditor");
    object.put("methode", "rotate");
    arguments.put("uuid", uuid);
    arguments.put("degree", degree);
    object.add_child("arguments", arguments);

    send(to_string(object));
}

std::shared_ptr<PhotoEditorInfo> PhotoEditor::info() {
    boost::property_tree::ptree object;
    boost::property_tree::ptree arguments;

    object.put("object", "PhotoEditor");
    object.put("methode", "info");

    Message reply = send(to_string(object));

    boost::property_tree::ptree reply_tree;
    std::istringstream is (reply.body());
    boost::property_tree::read_json (is, reply_tree);

    return std::make_shared<PhotoEditorInfo>(reply_tree.get<std::string>("arguments.image"),
        reply_tree.get<int>("arguments.degree"));
}

Message PhotoEditor::send(const std::string& json) {
    Message msg;
    msg.body_length(json.length());
    std::memcpy(msg.body(), json.c_str(), msg.body_length());
    msg.encode_header();
 
    boost::asio::io_service io_service;
    
    TransportSync transport{io_service, "127.0.0.1", "5001"};
    transport.send(msg);
    Message reply = transport.reply();

    return reply;
}

} // namespace client