//
// Created by guigui on 9/18/19.
//

#ifndef CPP_BABEL_2019_UDPNETWORK_HPP
#define CPP_BABEL_2019_UDPNETWORK_HPP

#include <QtCore/QTextStream>
#include <QUdpSocket>
#include <QWidget>

class UdpNetwork : public QWidget {
public:
    UdpNetwork(std::string &host, int port);
    ~UdpNetwork();

    void sendData(std::string data);

    void closeConnection();

    QUdpSocket::SocketState getState();

    const std::string &getConnectedHostname() const;

    int getConnectedPort() const;

    const std::string getLocalIp() const;

    std::string getConnectedHostWithDomain() const;

    std::string getLocalHostWithDomain() const;

    quint16 getLocalPort() const;

private slots:
    void handleError(int err);
private:
    QUdpSocket *socket;
    std::string host;
    int port;
};

#endif //CPP_BABEL_2019_UDPNETWORK_HPP
