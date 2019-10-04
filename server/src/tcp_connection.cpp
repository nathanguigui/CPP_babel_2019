#include "Server.hpp"

std::string make_daytime_string(); 

void connection_handler::start()
{
    read_data();
}
void connection_handler::read_data()
{
    sock.async_read_some(
      boost::asio::buffer(data, max_length),
      boost::bind(&connection_handler::handle_read,
                  shared_from_this(),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
}

void connection_handler::write_data()
{
    buffer = header_manager.response_header;
    sock.async_write_some(
        boost::asio::buffer(buffer, max_length),
        boost::bind(&connection_handler::handle_write,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void connection_handler::handle_read(const boost::system::error_code& err, size_t bytes_transferred)
{
    std::string new_data;
    if (!err) {
        new_data = convertToString(data);
        std::cout << new_data << std::endl;
        header_manager.parse_header(new_data);
        reply_to_msg();
        memset((char *) data, 0, max_length);
    } else {
        sock.close();
    }
}
void connection_handler::handle_write(const boost::system::error_code& err, size_t bytes_transferred)
{
    std::cout << buffer << std::endl;
    start();
}

void connection_handler::handle_write_header(const boost::system::error_code& err, size_t bytes_transferred)
{
    buffer.clear();
    header_manager.response_header.clear();
}

void connection_handler::write_header()
{
    buffer = header_manager.response_header;
    std::cout << buffer << std::endl;
    boost::asio::async_write(sock,
        boost::asio::buffer(buffer, buffer.size()),
        boost::bind(&connection_handler::handle_write_header,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void wait_handler(const boost::system::error_code& error)
{
  if (!error)
  {
    // Wait succeeded.
  }
}

void connection_handler::wait_for_write()
{
    sock.async_wait(boost::asio::ip::tcp::socket::wait_write, wait_handler);
}

void connection_handler::send_it()
{
    write_header();
}

void connection_handler::reply_to_msg()
{
    if (header_manager.get_request_types() == request_types::REGISTER) {
        header_manager.trying_connection();
        send_it();
        header_manager.OK_header();
        send_it();
        header_manager.notify_header("Connected");
        send_it();
        header_manager.check_account_existing();
    }
}