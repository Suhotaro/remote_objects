#pragma once

#include <string>
#include <memory>

#include "message.hpp"

namespace client {

struct PhotoEditorInfo {
    PhotoEditorInfo(const std::string& _image, int _degree) :
        image{_image}, degree{_degree}
        {}
    std::string image;
    int degree = 0;
};

class PhotoEditor final {
public:
    void create(int uuid = 0);

    void upload(const std::string& image);
    void rotate(int degree);

    std::shared_ptr<PhotoEditorInfo> info();

private:
    Message send(const Message& msg);
    int uuid = 0;
};

} // namespace client
