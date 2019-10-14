//
// Created by guigui on 9/18/19.
//

#include <iostream>
#include <sstream>
#include "Network/UdpNetwork.hpp"

UdpNetwork::UdpNetwork(std::string &host, int port, void (*callback)(std::string, CallManager *),
                       CallManager *manager) : readCallback(callback), manager(manager), host(host), port(port), firstMessageDone(false) {
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
    auto tmp = QHostAddress(QString(this->host.c_str()));
    this->socket->writeDatagram(data.c_str(), data.size(), tmp, this->port);
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
    auto packet = this->readDatagram();
    UdpNetwork::SoundPacket soundPacket;
    AudioSettings::Encoded encoded;
    qDebug() << packet.c_str();
    /// send data to encode manager then to audio manager
    if (packet.size() >= sizeof(SoundPacket)) {
        std::memcpy(&soundPacket, packet.c_str(), packet.size());
        if (soundPacket.magic_code == 0x150407CA && soundPacket.timestamp >= this->currentTimestamp) {
            encoded.buffer.assign(soundPacket.sound, soundPacket.sound + sizeof(soundPacket.sound));
            encoded.size = soundPacket.soundSize;
            this->currentTimestamp = soundPacket.timestamp;
            emit PacketRecieved(encoded);
        }
    }
}

void UdpNetwork::readyReadClient() {
    auto packet = this->readDatagram();
    UdpNetwork::SoundPacket soundPacket;
    AudioSettings::Encoded encoded;
    qDebug() << packet.c_str();
    /// send data to encode manager then to audio manager
    if (!this->firstMessageDone)
        this->sendData("hello world");
    if (packet.size() >= sizeof(SoundPacket)) {
        std::memcpy(&soundPacket, packet.c_str(), packet.size());
        if (soundPacket.magic_code == 0x150407CA && soundPacket.timestamp >= this->currentTimestamp) {
            encoded.buffer.assign(soundPacket.sound, soundPacket.sound + sizeof(soundPacket.sound));
            encoded.size = soundPacket.soundSize;
            this->currentTimestamp = soundPacket.timestamp;
            emit PacketRecieved(encoded);
        }
    }
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
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
    if (!this->firstMessageDone && buffer.toStdString() == "hello world") {
        qDebug() << "Message from: " << sender.toString();
        qDebug() << "Message port: " << senderPort;
        qDebug() << "Message: " << buffer;
        this->firstMessageDone = true;
        this->host = sender.toString().toStdString();
        this->port = senderPort;
    } else if (this->firstMessageDone && sender.toString().toStdString() == this->host)
        return buffer.toStdString();
    qDebug() << "message: " << buffer;
    return "";
}
