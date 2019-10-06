#include "../includes/Server.hpp"

void Server::start_accept()
{
    connection_handler::pointer new_connection = connection_handler::create(io_context_);

    acceptor_.async_accept(new_connection->socket(),
        boost::bind(&Server::handle_accept, this, new_connection,
        boost::asio::placeholders::error));
}
void Server::handle_accept(connection_handler::pointer new_connection, const boost::system::error_code& err)
{
    if (!err)
    {
      manager_.start(new_connection);
    }
    start_accept();
}