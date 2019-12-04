#include "client.hpp"
#include "photo_editor.hpp"
#include "stream.hpp"

namespace client {

std::shared_ptr<PhotoEditor> Client::make_photo_editor(int uuid) {
    std::shared_ptr<PhotoEditor> photo_editor = std::make_shared<PhotoEditor>();
    photo_editor->create(uuid);
    return photo_editor;
}

std::shared_ptr<Stream> Client::make_stream(int uuid) {
    std::shared_ptr<Stream> photo_editor = std::make_shared<Stream>();
    photo_editor->create(uuid);
    return photo_editor;
}

} // namespace client
