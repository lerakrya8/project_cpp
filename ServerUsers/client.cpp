//
// Created by lerakrya on 09.12.2020.
//

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main() {
    boost::asio::io_service service;
    tcp::endpoint end(boost::asio::ip::address::from_string("127.0.0.1"), 8081);
    tcp::socket socket(service);
    socket.async_connect(end, [&socket] (const boost::system::error_code& err) {
        std::string requst = "priver server";

        if(!err) {
            boost::asio::write(socket, boost::asio::buffer(requst));
        }
    });
    service.run();

    return 0;
}