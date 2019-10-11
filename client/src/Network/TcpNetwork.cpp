//
// Created by guigui on 9/25/19.
//

#include <iostream>
#include <sstream>
#include "Network/TcpNetwork.hpp"
#include <QAbstractSocket>
#include <QtNetwork/QHostAddress>
#include <boost/thread/thread.hpp>

TcpNetwork::TcpNetwork(std::string &host, int port, void (*readCallback)(std::string, SessionManager *),
                       SessionManager *manager) : readCallback(readCallback), sessionManager(manager), host(host), port(port) {
    this->socket = new QTcpSocket();
    this->socket->setSocketOption(QAbstractSocket::LowDelayOption, true);
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(this->socket, SIGNAL(connected()), this, SLOT(connected()));
    socket->connectToHost(host.c_str(), port);
    if (!socket->waitForConnected(3000))
        qDebug() << "connection timeout\n";
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
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    auto item = QNetworkInterface::allAddresses();
    std::string tmp = "127.0.0.1:" + std::to_string(this->socket->localPort());
    for (const QHostAddress &address: item) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost) {
            tmp = address.toString().toStdString() + ":" + std::to_string(this->socket->localPort());
        }
        return tmp;
    }
    return tmp;
}

quint16 TcpNetwork::getLocalPort() const {
    return 0;
}

void TcpNetwork::handleError(int err) {
    std::cerr << "Error nb" << err << std::endl;
}

void TcpNetwork::readyRead() {
    this->readCallback(this->socket->readAll().toStdString(), this->sessionManager);
}

void TcpNetwork::connected() {
    qDebug() << "Network connected\n";
}