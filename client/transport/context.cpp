#include "context.hpp"

namespace client
{

void Context::start() {
    io_service_thread = std::thread{[this]() {
        boost::asio::io_service::work work(io_service);
        io_service.run();
    }};
}

void Context::stop() {
    io_service.stop();
    io_service_thread.join();
}

} // namespace client
