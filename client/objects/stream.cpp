#include "stream.hpp"
#include "transport_sync.hpp"
#include "util.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>

namespace client {

Stream::Stream() : Transport(service(), "127.0.0.1", "5001")
{}

void Stream::start() {
    Context::start();
    Transport::start();
}

void Stream::stop() {
    Transport::stop();
    Context::stop();
}

void Stream::create(int _uuid) {
    boost::property_tree::ptree object;
    boost::property_tree::ptree arguments;

    object.put("object", "Stream");
    object.put("methode", "create");
    arguments.put("uuid", _uuid);
    object.add_child("arguments", arguments);

    TransportSync transport{"127.0.0.1", "5001"};
    Message reply = transport.send(to_msg(to_string(object)));

    boost::property_tree::ptree reply_tree;
    std::istringstream is (std::string(reply.body(), reply.body_length()));
    boost::property_tree::read_json (is, reply_tree);

    uuid = reply_tree.get<int>("arguments.uuid");
    printf("Stream uuid %d\n", uuid);
}

void Stream::send_chat_msg(const std::string& msg) {
    boost::property_tree::ptree object;
    boost::property_tree::ptree arguments;

    object.put("object", "Stream");
    object.put("methode", "send_chat_msg");
    arguments.put("uuid", uuid);
    arguments.put("msg", msg);
    object.add_child("arguments", arguments);

    send(to_msg(to_string(object)));
}

void Stream::donate(int _donation) {
    boost::property_tree::ptree object;
    boost::property_tree::ptree arguments;

    object.put("object", "Stream");
    object.put("methode", "donate");
    arguments.put("uuid", uuid);
    arguments.put("donation", _donation);
    object.add_child("arguments", arguments);

    send(to_msg(to_string(object)));
}

void Stream::on_msg_received(const Message& msg) {
    boost::property_tree::ptree msg_tree;
    std::istringstream is (std::string(msg.body(), msg.body_length()));
    boost::property_tree::read_json (is, msg_tree);

    if (msg_tree.get<std::string>("methode") == "on_chat_msg")
        on_chat_msg(msg_tree.get<std::string>("arguments.msg"));
    else if (msg_tree.get<std::string>("methode") == "on_donation")
        on_donation(msg_tree.get<int>("arguments.donation"));
}

void Stream::on_chat_msg(std::string msg) {
    printf("Stream(id:%d): msg: %s\n", uuid, msg.c_str());
}

void Stream::on_donation(int _vlaue) {
    printf("Stream(id:%d): donation: %d\n", uuid, _vlaue);
}

} // namespace client
