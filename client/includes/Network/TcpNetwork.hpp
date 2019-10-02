//
// Created by guigui on 9/25/19.
//

#ifndef CPP_BABEL_2019_TCPNETWORK_HPP
#define CPP_BABEL_2019_TCPNETWORK_HPP

#include <QtCore/QTextStream>
#include <QTcpSocket>
#include <QWidget>
#include <QNetworkInterface>
#include <sstream>
#include "IProtoNetwork.hpp"

class TcpNetwork : public QObject, public IProtoNetwork {
    Q_OBJECT
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

public slots:
    void readyRead();
    void connected();

private slots:
    void handleError(int err);
private:
    QTcpSocket *socket;
    std::string host;
    int port;
};

#endif //CPP_BABEL_2019_TCPNETWORK_HPP
