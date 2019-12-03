#pragma once

#include <map>
#include <memory>
#include <mutex>


namespace server {

class Object;

class AvlTree {
public:
    std::shared_ptr<Object> make_photo_editor();
    std::shared_ptr<Object> make_stream();
    
    std::shared_ptr<Object> find(int uuid);

private:
    std::mutex tree_mutex;
    std::map<int, std::shared_ptr<Object>> tree;
    int uuid = 0;
};

} // namespace server
