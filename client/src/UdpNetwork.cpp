//
// Created by guigui on 9/18/19.
//

#include <iostream>
#include "UdpNetwork.hpp"

UdpNetwork::UdpNetwork(std::string &host, int port) {
    this->socket = new QUdpSocket();
    this->socket->connect(this->socket, SIGNAL(error(int)), SLOT(this.handleError(int)));
    socket->connectToHost(host.c_str(), port);
}

void UdpNetwork::sendData(std::string data) {
    QTextStream os(this->socket);
    os << data.c_str() << "\n";
}

void UdpNetwork::closeConnection() {
    this->socket->close();
}

QUdpSocket::SocketState UdpNetwork::getState() {
    return (this->socket->state());
}

void UdpNetwork::handleError(int err) {
    std::cerr << "Error nb" << err << std::endl;
}
