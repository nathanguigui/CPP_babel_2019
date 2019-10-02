//
// Created by guigui on 9/25/19.
//

#include <iostream>
#include <sstream>
#include "Network/TcpNetwork.hpp"
#include <qabstractsocket.h>

TcpNetwork::TcpNetwork(std::string &host, int port) {
    this->socket = new QTcpSocket();
    socket->connectToHost(host.c_str(), port);
}

TcpNetwork::~TcpNetwork() {
    if (socket)
        delete(socket);
}

void TcpNetwork::sendData(std::string data) {
    QTextStream os(this->socket);
    os << data.c_str();
}

void TcpNetwork::closeConnection() {
    this->socket->close();
}

QTcpSocket::SocketState TcpNetwork::getState() {
    return (this->socket->state());
}

const std::string &TcpNetwork::getConnectedHostname() const {
    return host;
}

int TcpNetwork::getConnectedPort() const {
    return port;
}

const std::string TcpNetwork::getLocalIp() const {
    return "this->socket->localAddress().toString().toStdString()";
}

std::string TcpNetwork::getConnectedHostWithDomain() const {
    return std::string();
}

std::string TcpNetwork::getLocalHostWithDomain() const {
    return std::string();
}

quint16 TcpNetwork::getLocalPort() const {
    return 0;
}

void TcpNetwork::handleError(int err) {
    std::cerr << "Error nb" << err << std::endl;
}
