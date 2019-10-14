//
// Created by guigui on 9/18/19.
//

#ifndef CPP_BABEL_2019_UDPNETWORK_HPP
#define CPP_BABEL_2019_UDPNETWORK_HPP

#include <QtCore/QTextStream>
#include <QUdpSocket>
#include <QWidget>
#include "IProtoNetwork.hpp"

class CallManager;

enum UdpNetworkMode {
    NO_MODE,
    SERVER,
    CLIENT
};

class UdpNetwork : public QWidget, public IProtoNetwork {
    Q_OBJECT
public:
    /// Create Udp Client
    UdpNetwork(std::string &host, int port, void (*callback)(std::string, CallManager *), CallManager *manager);
    /// Create Udp Server
    UdpNetwork();
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

    UdpNetworkMode getMode() const;

    int getPort() const;

    void startServer();

signals:
    /// Signal to tell to callManager server ready
    void ServerReady(int port);

public slots:
    void readyReadServer();
    void readyReadClient();
    void connectedClient();
    void connectedServer();

private slots:
    void handleError(int err);
private:
    std::string readDatagram();

    QUdpSocket *socket;
    std::string host;
    int port;
    UdpNetworkMode mode;
    CallManager *manager;
    void (*readCallback)(std::string, CallManager *manager);
};

#endif //CPP_BABEL_2019_UDPNETWORK_HPP
