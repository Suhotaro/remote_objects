#pragma once

#include "object.hpp"

namespace server {

class Stream final : public Object {
public:
    Stream(int uuid) : Object(uuid) {}

    virtual void on_msg_received(std::shared_ptr<Transport>, const Message&) override {}
};

} // namespace server
