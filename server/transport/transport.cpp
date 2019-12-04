#include "transport.hpp"
#include "acceptor.hpp"
#include "util.hpp"

// TODO: rm
#include <iostream>


namespace server
{

Transport::Transport(std::shared_ptr<Acceptor> _acceptor,
    boost::asio::io_service& io_service)
: acceptor{_acceptor}
, socket{io_service}
{}

bool Transport::start() {
    do_read_header();
}

boost::asio::ip::tcp::socket& Transport::socket_get() {
    return socket;
}

void Transport::send(const Message& msg) {
    //dump(msg);
    bool write_in_progress = !write_msgs.empty();
    write_msgs.push_back(msg);
    if (!write_in_progress)
        do_write();
}

void Transport::do_read_header() {
    auto self(shared_from_this());
    boost::asio::async_read(socket,
        boost::asio::buffer(read_msg.data(), Message::header_length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
            if (!ec && read_msg.decode_header())
                do_read_body();
            else {
                acceptor->unregister_transport(self);
            }
        });
}

void Transport::do_read_body() {
    auto self(shared_from_this());
    boost::asio::async_read(socket,
        boost::asio::buffer(read_msg.body(), read_msg.body_length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
            if (!ec) {
                on_msg_received(read_msg);
                do_read_header();
            } else {
                printf("ERROR: do_read_body(%s)\n", ec.message().c_str());
                acceptor->unregister_transport(self);      
            }
        });
}

void Transport::do_write() {
    auto self(shared_from_this());
    boost::asio::async_write(socket,
        boost::asio::buffer(write_msgs.front().data(), write_msgs.front().length()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
            if (!ec) {
                write_msgs.pop_front();
                if (!write_msgs.empty())
                    do_write();
            } else {
                printf("ERROR: do_write(%s)\n", ec.message().c_str());
                acceptor->unregister_transport(self);             
            }
    });
}

}//namespace server
