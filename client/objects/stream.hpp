#pragma once

#include "transport.hpp"
#include "context.hpp"
#include "message.hpp"

namespace client {

class Stream final : public Context, public Transport {
public:
    Stream();

    void start();
    void stop();

    void create(int uuid = 0);

    void send_chat_msg(const std::string& msg);
    void donate(int donation);

private:
    virtual void on_msg_received(const Message& msg) override;

    void on_chat_msg(std::string msg);
    void on_donation(int donation);

    int uuid = 0;
};

} // namespace client
