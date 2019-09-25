//
// Created by guigui on 9/18/19.
//

#ifndef CPP_BABEL_2019_UDPNETWORK_HPP
#define CPP_BABEL_2019_UDPNETWORK_HPP

#include <QtCore/QTextStream>
#include <QUdpSocket>
#include <QWidget>
#include "IProtoNetwork.hpp"

class UdpNetwork : public QWidget, public IProtoNetwork {
public:
    UdpNetwork(std::string &host, int port);
    ~UdpNetwork() override;

    void sendData(std::string data) override;

    void closeConnection() override;

    QUdpSocket::SocketState getState();

    const std::string &getConnectedHostname() const override;

    int getConnectedPort() const override;

    const std::string getLocalIp() const override;

    std::string getConnectedHostWithDomain() const override;

    std::string getLocalHostWithDomain() const override;

    quint16 getLocalPort() const override;

private slots:
    void handleError(int err);
private:
    QUdpSocket *socket;
    std::string host;
    int port;
};

#endif //CPP_BABEL_2019_UDPNETWORK_HPP
