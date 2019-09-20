//
// Created by guigui on 9/18/19.
//

#include <iostream>
#include <sstream>
#include "Network/UdpNetwork.hpp"

UdpNetwork::UdpNetwork(std::string &host, int port) {
    this->socket = new QUdpSocket();
    socket->connectToHost(host.c_str(), port);
}

UdpNetwork::~UdpNetwork() {
    if (socket)
        delete(socket);
}

void UdpNetwork::sendData(std::string data) {
    QTextStream os(this->socket);
    os << data.c_str();
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

const std::string &UdpNetwork::getConnectedHostname() const {
    return host;
}

int UdpNetwork::getConnectedPort() const {
    return port;
}

quint16 UdpNetwork::getLocalPort() const {
    return this->socket->localPort();
}

const std::string UdpNetwork::getLocalIp() const {
    return this->socket->localAddress().toString().toStdString();
}

std::string UdpNetwork::getConnectedHostWithDomain() const {
    auto ss = std::stringstream();
    ss << getConnectedHostname() << ":" << getConnectedPort();
    return ss.str();
}

std::string UdpNetwork::getLocalHostWithDomain() const {
    auto ss = std::stringstream();
    ss << getLocalIp() << ":" << getLocalPort();
    return ss.str();
}
