#include "util.hpp"

namespace server {

std::string to_string(const boost::property_tree::ptree& tree)  {
    std::ostringstream oss;
    boost::property_tree::write_json(oss, tree, false);
    return oss.str();
}

Message to_msg(const std::string& json) {
    Message msg;
    msg.body_length(json.length());
    std::memcpy(msg.body(), json.c_str(), msg.body_length());
    msg.encode_header();
    return msg;
}

void dump(const Message& msg) {
    printf("BUFFER: %s\n", msg.body());
}

} // namespace server
