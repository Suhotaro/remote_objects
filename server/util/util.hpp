#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>

#include "message.hpp"

namespace server {

std::string to_string(const boost::property_tree::ptree& tree);
Message to_msg(const std::string& json);


} // namespace server
