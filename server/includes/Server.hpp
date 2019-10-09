#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <set>
#include <boost/array.hpp>
#include <stdlib.h>
#include <string.h>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/ip/address.hpp>
#include "SipManager.hpp"

using boost::asio::ip::tcp;
class connection_manager;
std::string convertToString(char* a);

class connection_handler : public boost::enable_shared_from_this<connection_handler>
{
    public:
        typedef boost::shared_ptr<connection_handler> pointer;
        connection_handler(boost::asio::io_service& io_service): sock(io_service){ data = (char *)malloc(sizeof(char ) * max_length);boost::asio::ip::tcp::no_delay option(true);
            boost::system::error_code ec;
            sock.set_option(option, ec);
            if (ec)
            {
              // An error occurred.
            }
}
        static pointer create(boost::asio::io_service& io_service){return pointer(new connection_handler(io_service));}
        tcp::socket& socket(){return sock;}
        void start();
        void write_data();
        void read_data();
        void handle_read(const boost::system::error_code& err, size_t bytes_transferred);
        void handle_write(const boost::system::error_code& err, size_t bytes_transferred);
        void reply_to_msg(std::string header);
        void write_header();
        void handle_write_header(const boost::system::error_code& err, size_t bytes_transferred);
        void wait_for_write();
        void send_it();
    private:
        SipManager header_manager;
        tcp::socket sock;
        std::string buffer;
        enum { max_length = 8192};
        char *data;
};

class connection_manager {
    public:
        connection_manager(){};
        void start(connection_handler::pointer);
        void stop(connection_handler::pointer);
        void stop_all();
    private:
        std::set<connection_handler::pointer> connections_;
};


class Server {
    public:
        Server(boost::asio::io_service& io_service): manager_(),io_context_(io_service), acceptor_(io_service, tcp::endpoint(boost::asio::ip::address::from_string("192.168.1.30"), 25565)){start_accept();}
        void handle_accept(connection_handler::pointer new_connection, const boost::system::error_code& err);
    private:
        tcp::acceptor acceptor_;
        boost::asio::io_context& io_context_;
        void start_accept();
        connection_manager manager_;

};