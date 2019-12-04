#pragma once

#include "object.hpp"

#include <list>

namespace server {

class Stream final : public Object {
public:
    Stream(int uuid) : Object(uuid) {}

    virtual void on_msg_received(std::shared_ptr<Transport>, const Message&) override;

private:
    void on_send_chat_msg(std::shared_ptr<Transport>, const std::string& image);
    void on_donate(std::shared_ptr<Transport>, int degree);

    std::list<std::string> msgs;
    std::list<int> donations;
};

} // namespace server
