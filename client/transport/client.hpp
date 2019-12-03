#pragma once

#include <memory>
#include <vector>

namespace client {

class PhotoEditor;

class Client final {
public:
    std::shared_ptr<PhotoEditor> make_photo_editor(int uuid = 0);
    std::vector<int> remote_photo_editors();
};

} // namespace client
