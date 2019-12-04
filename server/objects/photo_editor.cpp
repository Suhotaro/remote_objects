#include "object.hpp"
#include "message.hpp"
#include "photo_editor.hpp"
#include "util.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>


namespace server {

void PhotoEditor::on_msg_received(std::shared_ptr<Transport> trasnport, const Message& msg) {
    boost::property_tree::ptree msg_tree;
    std::istringstream is (msg.body());
    boost::property_tree::read_json (is, msg_tree);

    if (msg_tree.get<std::string>("methode") == "upload")
        on_upload(trasnport, msg_tree.get<std::string>("arguments.image"));
    else if (msg_tree.get<std::string>("methode") == "rotate")
        on_rotate(trasnport, msg_tree.get<int>("arguments.degree"));
}

void PhotoEditor::on_upload(std::shared_ptr<Transport> transport, const std::string& _image) {
    image = _image;
    printf("SERVER: PhotoEditor::on_upload %s\n", image.c_str());

    boost::property_tree::ptree reply_object;
    boost::property_tree::ptree reply_arguments;

    reply_object.put("object", "PhotoEditor");
    reply_object.put("methode", "upload");
    reply_arguments.put("uuid", id());
    reply_object.add_child("arguments", reply_arguments);

    transport->send(to_msg(to_string(reply_object)));
}

void PhotoEditor::on_rotate(std::shared_ptr<Transport> transport, int _degree) {
    degree = _degree;
    printf("SERVER: PhotoEditor::on_rotate %d\n", degree);

    boost::property_tree::ptree reply_object;
    boost::property_tree::ptree reply_arguments;

    reply_object.put("object", "PhotoEditor");
    reply_object.put("methode", "rotated");
    reply_arguments.put("uuid", id());
    reply_object.add_child("arguments", reply_arguments);

    transport->send(to_msg(to_string(reply_object)));    
}

} // namespace server
