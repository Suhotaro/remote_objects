#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace server
{

class Message
{
public:
    enum { header_length = 4 };
    enum { max_body_length = 512 };

    Message();

    bool decode_header();
    void encode_header();

    std::size_t length() const;

    const char* data() const;
    char* data();

    const char* body() const;
    char* body();
    std::size_t body_length() const;
    void body_length(std::size_t new_length);

private:
    char _data[header_length + max_body_length];
    std::size_t _body_length;
};

} // namespace server
