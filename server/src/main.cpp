#include "Server.hpp"


int main()
{
    boost::asio::io_service io_service;
    udp_server server(io_service);
    io_service.run();
}