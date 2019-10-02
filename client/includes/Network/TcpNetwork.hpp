//
// Created by guigui on 9/25/19.
//

#ifndef CPP_BABEL_2019_TCPNETWORK_HPP
#define CPP_BABEL_2019_TCPNETWORK_HPP

#include <QtCore/QTextStream>
#include "IProtoNetwork.hpp"
#include <QTcpSocket>
#include <QWidget>

class TcpNetwork : public QObject, public IProtoNetwork {
public:
    TcpNetwork(std::string &host, int port);
    ~TcpNetwork() override;

    void sendData(std::string data) override;

    void closeConnection() override;

    QTcpSocket::SocketState getState();

    const std::string &getConnectedHostname() const override;

    int getConnectedPort() const override;

    const std::string getLocalIp() const override;

    std::string getConnectedHostWithDomain() const override;

    std::string getLocalHostWithDomain() const override;

    quint16 getLocalPort() const override;

private slots:
    void handleError(int err);
private:
    QTcpSocket *socket;
    std::string host;
    int port;
};

#endif //CPP_BABEL_2019_TCPNETWORK_HPP
