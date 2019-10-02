#include "Server.hpp"

std::string make_daytime_string(); 

void connection_handler::start()
{
  sock.async_read_some(
      boost::asio::buffer(data, max_length),
      boost::bind(&connection_handler::handle_read,
                  shared_from_this(),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
        sock.async_write_some(
        boost::asio::buffer(buffer, max_length),
        boost::bind(&connection_handler::handle_write,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}
void connection_handler::handle_read(const boost::system::error_code& err, size_t bytes_transferred)
{
        buffer = "Wesh les zgegs";
    if (!err) {
        std::cout << data << std::endl;
        memset((char *) data, 0, max_length);
    } else {
        sock.close();
    }
}
void connection_handler::handle_write(const boost::system::error_code& err, size_t bytes_transferred)
{
    buffer.clear();
    start();
}