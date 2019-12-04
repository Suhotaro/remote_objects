#pragma once

#include "object.hpp"

namespace server {

class PhotoEditor final : public Object {
public:
    PhotoEditor(int uuid) : Object(uuid) {}

    virtual void on_msg_received(std::shared_ptr<Transport>, const Message&) override;

private:
    void on_upload(std::shared_ptr<Transport>, const std::string& image);
    void on_rotate(std::shared_ptr<Transport>, int degree);
    void on_info(std::shared_ptr<Transport>);

    std::string image;
    int degree = 0;
};

} // namespace server
