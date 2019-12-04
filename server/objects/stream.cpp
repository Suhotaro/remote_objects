#include "stream.hpp"
#include "util.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>


namespace server {

void Stream::on_msg_received(std::shared_ptr<Transport> trasnport, const Message& msg) {
    boost::property_tree::ptree msg_tree;
    std::istringstream is (msg.body());
    boost::property_tree::read_json (is, msg_tree);

    if (msg_tree.get<std::string>("methode") == "send_chat_msg")
        on_send_chat_msg(trasnport, msg_tree.get<std::string>("arguments.msg"));
    else if (msg_tree.get<std::string>("methode") == "donate")
        on_donate(trasnport, msg_tree.get<int>("arguments.value"));
}

void Stream::on_send_chat_msg(std::shared_ptr<Transport> transport, const std::string& msg) {
    msgs.push_back(msg);
    printf("SERVER: Stream::on_send_chat_msg %s\n", msg.c_str());

    boost::property_tree::ptree reply_object;
    boost::property_tree::ptree reply_arguments;

    reply_object.put("object", "Stream");
    reply_object.put("methode", "on_chat_msg");
    reply_arguments.put("uuid", id());
    reply_arguments.put("msg", msg);
    reply_object.add_child("arguments", reply_arguments);

    transport->send(to_msg(to_string(reply_object)));
}

void Stream::on_donate(std::shared_ptr<Transport> transport, int _donation) {
    donations.push_back(_donation);
    printf("SERVER: Stream::on_donate %d\n", _donation);

    boost::property_tree::ptree reply_object;
    boost::property_tree::ptree reply_arguments;

    reply_object.put("object", "Stream");
    reply_object.put("methode", "on_donation");
    reply_arguments.put("uuid", id());
    reply_arguments.put("donation", _donation);
    reply_object.add_child("arguments", reply_arguments);

    transport->send(to_msg(to_string(reply_object)));
}

} // namespace server
