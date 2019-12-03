#pragma once

namespace server {

class Object {
public:
    Object(int _uuid) : uuid(_uuid) {}

    int id() { return uuid; }

private:
    int uuid = 0;
};

} // namespace server
