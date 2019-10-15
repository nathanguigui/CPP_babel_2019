#include "../includes/Server.hpp"


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
        reply_to_msg(new_data);
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

Call_Data_Struct get_cli_from_packet(std::string packet)
{
    Call_Data_Struct data;
    packet.erase(0, packet.find("Waiting: ") + 9);
    data.uname = packet.substr(0, packet.find(":"));
    packet.erase(packet.find(";"), std::string::npos);
    data.port = packet.substr(packet.find(":") + 1);
    return data;
}


void connection_handler::send_header_to_cli(std::string packet)
{
    Call_Data_Struct cli_data = get_cli_from_packet(packet);
    auto hdr = std::stringstream();
    hdr << "567 INVITE sip:" <<  header_manager.get_ip() << "SIP/2.0";
    hdr << "\r\nVia: " << header_manager.get_ip() << ":" << cli_data.port;
    hdr << "\r\nFrom: \"" << header_manager.get_username() << "\" <sip:" << header_manager.get_username() << "@" <<header_manager.get_ip() << ">;tag=" << header_manager.get_tag_cli();
    hdr <<  "\r\nTo: <" << header_manager.get_hostname() << "@" << header_manager.get_server_ip() << ">";
    hdr << "\r\nContact: <sip:" << header_manager.get_username() <<"@" << header_manager.get_server_ip() << ">";
    hdr << "\r\nCSeq: 567 INVITE";
    hdr << "\r\nMessage_Waiting: ";
    for (auto it:connections_) {
        if (it->header_manager.get_username() == cli_data.uname && it->sock.is_open()) {
            hdr << header_manager.get_username() << ";" << header_manager.get_ip() << ";" << cli_data.port;
            it->header_manager.response_header = hdr.str();
            it->send_it();
            //std::cout << "trouver une correspondance\n";
        }
    }
}

void connection_handler::send_ack_to_cli(std::string packet)
{
    Call_Data_Struct cli_data = get_cli_from_packet(packet);
    auto hdr = std::stringstream();
    hdr << "123 ACK sip:" <<  header_manager.get_ip() << "SIP/2.0";
    hdr << "\r\nVia: " << header_manager.get_ip() << ":" << cli_data.port;
    hdr << "\r\nFrom: \"" << header_manager.get_username() << "\" <sip:" << header_manager.get_username() << "@" <<header_manager.get_ip() << ">;tag=" << header_manager.get_tag_cli();
    hdr <<  "\r\nTo: <" << header_manager.get_hostname() << "@" << header_manager.get_server_ip() << ">";
    hdr << "\r\nContact: <sip:" << header_manager.get_username() <<"@" << header_manager.get_server_ip() << ">";
    hdr << "\r\nCSeq: 123 ACK";
    hdr << "\r\nMessage_Waiting: ";
    for (auto it:connections_) {
        if (it->header_manager.get_username() == cli_data.uname && it->sock.is_open()) {
            hdr << header_manager.get_username() << "\r\n";
            it->header_manager.response_header = hdr.str();
            it->send_it();
            //std::cout << "trouver une correspondance\n";
        }
    }
}

void connection_handler::send_cancel_to_cli(std::string packet)
{
    Call_Data_Struct cli_data = get_cli_from_packet(packet);
    auto hdr = std::stringstream();
    hdr << "321 CANCEL sip:" <<  header_manager.get_ip() << "SIP/2.0";
    hdr << "\r\nVia: " << header_manager.get_ip() << ":" << cli_data.port;
    hdr << "\r\nFrom: \"" << header_manager.get_username() << "\" <sip:" << header_manager.get_username() << "@" <<header_manager.get_ip() << ">;tag=" << header_manager.get_tag_cli();
    hdr <<  "\r\nTo: <" << header_manager.get_hostname() << "@" << header_manager.get_server_ip() << ">";
    hdr << "\r\nContact: <sip:" << header_manager.get_username() <<"@" << header_manager.get_server_ip() << ">";
    hdr << "\r\nCSeq: 321 CANCEL";
    hdr << "\r\nMessage_Waiting: ";
    for (auto it:connections_) {
        if (it->header_manager.get_username() == cli_data.uname && it->sock.is_open()) {
            hdr << header_manager.get_username() << "\r\n";
            it->header_manager.response_header = hdr.str();
            it->send_it();
            //std::cout << "trouver une correspondance\n";
        }
    }
}

void connection_handler::reply_to_msg(std::string header)
{
        std::cout << header_manager.get_request_types()[header_manager.get_request_types().size() - 1] << std::endl;
    if (header_manager.get_request_types()[header_manager.get_request_types().size() - 1] == request_types::REGISTER) {
        header_manager.trying_connection();
        send_it();
        header_manager.OK_header();
        send_it();
        header_manager.notify_header("Connected");
        send_it();
        if (header_manager.check_account_existing() == 1) {
            for (auto it:connections_) {
                it->header_manager.info_header();
                it->send_it();
            }
        }
        header_manager.get_request_types().pop_back();
        start();
    } if (header_manager.get_request_types()[header_manager.get_request_types().size() - 1] == request_types::SUBSCRIBE) {
        std::cout << header_manager.get_request_types()[header_manager.get_request_types().size() - 1] << std::endl;
        header_manager.notify_header("Connected");
        send_it();
        header_manager.OK_header();
        send_it();
        header_manager.get_request_types().pop_back();
        start();
    } if (header_manager.get_request_types()[header_manager.get_request_types().size() - 1] == request_types::UPDATE) {
        header_manager.update_header();
        send_it();
        header_manager.get_request_types().pop_back();
        start();
    } if (header_manager.get_request_types()[header_manager.get_request_types().size() - 1] == request_types::ADD_FRIEND) {
        header_manager.add_friend_header(header);
        start();
        send_it();
        header_manager.get_request_types().pop_back();
    } if (header_manager.get_request_types()[header_manager.get_request_types().size() - 1] == request_types::INFO) {
        header_manager.info_header();
        send_it();
        header_manager.get_request_types().pop_back();
        start();
    } if (header_manager.get_request_types()[header_manager.get_request_types().size() - 1] == request_types::BYE) {
        header_manager.change_state();
        sock.close();
        for (auto it:connections_) {
            it->header_manager.info_header();
            it->send_it();
        }
    } if (header_manager.get_request_types()[header_manager.get_request_types().size() - 1] == request_types::INVITE) {
        send_header_to_cli(header);
        header_manager.get_request_types().pop_back();
        start();
    } 
    if (header_manager.get_request_types()[header_manager.get_request_types().size() - 1] == request_types::ACK) {
        send_ack_to_cli(header);
        start();
    } if (header_manager.get_request_types()[header_manager.get_request_types().size() - 1] == request_types::CANCEL) {
        send_cancel_to_cli(header);
        start();
    }
}