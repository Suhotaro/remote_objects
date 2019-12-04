#pragma once


namespace client {

class Message;

class Object {
public:
    int id() { return uuid; }
protected:
    int uuid = 0;
};

} // namespace server
