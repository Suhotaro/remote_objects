#pragma once

#include "object.hpp"

namespace server {

class PhotoEditor final : public Object {
public:
    PhotoEditor(int uuid) : Object(uuid) {}
};

} // namespace server
