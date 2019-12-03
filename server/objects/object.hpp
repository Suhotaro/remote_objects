#pragma once

#include "transport.hpp"
#include <memory>

namespace server {

class Message;

class Object {
public:
    Object(int _uuid) : uuid(_uuid) {}

    int id() { return uuid; }

    virtual void on_msg_received(std::shared_ptr<Transport>, const Message&) = 0;

private:
    int uuid = 0;
};

} // namespace server
