#include "client.hpp"
#include "photo_editor.hpp"

namespace client {

std::shared_ptr<PhotoEditor> Client::make_photo_editor(int uuid) {
    std::shared_ptr<PhotoEditor> photo_editor = std::make_shared<PhotoEditor>();
    photo_editor->create(uuid);
    return photo_editor;
}

std::vector<int> Client::remote_photo_editors() {
    return {};
}

} // namespace client
