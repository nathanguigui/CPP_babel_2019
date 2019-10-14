//
// Created by guigui on 9/18/19.
//

#include <iostream>
#include <sstream>
#include "Network/UdpNetwork.hpp"

UdpNetwork::UdpNetwork(std::string &host, int port, void (*callback)(std::string, CallManager *),
                       CallManager *manager) : readCallback(callback), manager(manager) {
    this->socket = new QUdpSocket();
    this->mode = CLIENT;
    this->socket->setSocketOption(QAbstractSocket::LowDelayOption, true);
    connect(socket, SIGNAL(connected()), this, SLOT(connectedClient()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyReadClient()));
    qDebug() << "connecting to peer in UDP\r\n";
    socket->connectToHost(host.c_str(), port);
    if (!socket->waitForConnected(3000))
        qDebug() << "connection timeout\n";
}

UdpNetwork::UdpNetwork() {
    this->socket = new QUdpSocket();
    this->socket->setSocketOption(QAbstractSocket::LowDelayOption, true);
    connect(socket, SIGNAL(connected()), this, SLOT(connectedServer()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyReadServer()));
    this->mode = SERVER;
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

UdpNetworkMode UdpNetwork::getMode() const {
    return mode;
}

void UdpNetwork::readyReadServer() {
    this->readDatagram();
}

void UdpNetwork::readyReadClient() {
    this->readDatagram();
}

int UdpNetwork::getPort() const {
    return port;
}

void UdpNetwork::startServer() {
    socket->bind();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyReadServer()));
    this->port = this->socket->localPort();
    qDebug() << "ServerReady Signal emited\r\n";
    emit ServerReady(this->port);
}

void UdpNetwork::connectedClient() {
    qDebug() << "call connectted to peer\r\n";
}

void UdpNetwork::connectedServer() {
    qDebug() << "friend join P2P UDP server\r\n";
}

std::string UdpNetwork::readDatagram() {
    // when data comes in
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    // qint64 QUdpSocket::readDatagram(char * data, qint64 maxSize,
    //                 QHostAddress * address = 0, quint16 * port = 0)
    // Receives a datagram no larger than maxSize bytes and stores it in data.
    // The sender's host address and port is stored in *address and *port
    // (unless the pointers are 0).

    socket->readDatagram(buffer.data(), buffer.size(),
                         &sender, &senderPort);

    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;
    return buffer.toStdString();
}
