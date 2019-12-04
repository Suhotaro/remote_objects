#pragma once

#include <boost/asio.hpp>

#include <thread>

namespace client
{

class Context
{
public:
    void start();
    void stop();

    boost::asio::io_service& service() { return io_service; }

private:
    boost::asio::io_service io_service;
    std::thread io_service_thread; 
};

} // namespace client
