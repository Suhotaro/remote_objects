#include "message.hpp"

namespace client
{

Message::Message() :_body_length{0}
{}

bool Message::decode_header() {
    char header[header_length + 1] = "";
    std::strncat(header, _data, header_length);
    _body_length = std::atoi(header);
    if (_body_length > max_body_length) {
        _body_length = 0;
        return false;
    }
    return true;
}

void Message::encode_header() {
    char header[header_length + 1] = "";
    std::sprintf(header, "%4d", static_cast<int>(_body_length));
    std::memcpy(_data, header, header_length);
}

const char* Message::data() const {
    return _data;
}

char* Message::data() {
    return _data;
}

std::size_t Message::length() const {
    return header_length + _body_length;
}

const char* Message::body() const {
    return _data + header_length;
}

char* Message::body() {
    return _data + header_length;
}

std::size_t Message::body_length() const {
    return _body_length;
}

void Message::body_length(std::size_t new_length) {
    _body_length = new_length;
    if (_body_length > max_body_length)
        _body_length = max_body_length;
}

} // namespace client
