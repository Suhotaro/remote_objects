#include "context.hpp"

namespace client
{

void Context::start() {
    io_service_thread = std::thread{[this]() {
        try {
            boost::asio::io_service::work work(io_service);
            io_service.run();
        } catch(...) {}
    }};
}

void Context::stop() {
    try {
        io_service.stop();
        io_service_thread.join();    
    } catch(...) {}    
}

} // namespace client
