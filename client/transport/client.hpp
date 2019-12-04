#pragma once

#include <memory>
#include <vector>

#include "stream.hpp"

namespace client {

class PhotoEditor;

class Client final {
public:
    std::shared_ptr<PhotoEditor> make_photo_editor(int uuid = 0);
    std::shared_ptr<Stream> make_stream(int uuid = 0);
};

} // namespace client
