#pragma once

#include "object.hpp"
#include <atomic>
#include <mutex>

namespace server {

class PhotoEditor final : public Object {
public:
    PhotoEditor(int uuid) : Object(uuid) {}

    virtual void on_msg_received(std::shared_ptr<Transport>, const Message&) override;

private:
    void on_upload(std::shared_ptr<Transport>, const std::string& image);
    void on_rotate(std::shared_ptr<Transport>, int degree);
    void on_info(std::shared_ptr<Transport>);

    std::mutex image_mutex;
    std::string image;

    std::atomic<int> degree{0};
};

} // namespace server
