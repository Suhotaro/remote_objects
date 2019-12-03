#include "avl_tree.hpp"
#include "object.hpp"

#include "photo_editor.hpp"
#include "stream.hpp"

namespace server {

std::shared_ptr<Object> AvlTree::make_photo_editor() {
    tree_mutex.lock();

    std::shared_ptr<Object> o = std::make_shared<PhotoEditor>(++uuid);
    tree.insert({o->id(), o});

    tree_mutex.unlock();
    printf("SERVER: make_photo_editor id:%d\n", o->id());
    return o;
}

std::shared_ptr<Object> AvlTree::make_stream() {
    tree_mutex.lock();

    std::shared_ptr<Object> o = std::make_shared<Stream>(++uuid);
    tree.insert({o->id(), o});
    
    tree_mutex.unlock();
    printf("SERVER: make_stream id:%d\n", o->id());
    return o;
}

std::shared_ptr<Object> AvlTree::find(int uuid) {
    auto res = tree.find(uuid);
    if (res == tree.end())
        return std::shared_ptr<Object>();
    return res->second;
}

} // namespace server