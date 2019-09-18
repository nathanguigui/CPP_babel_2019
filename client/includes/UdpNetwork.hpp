//
// Created by guigui on 9/18/19.
//

#ifndef CPP_BABEL_2019_UDPNETWORK_HPP
#define CPP_BABEL_2019_UDPNETWORK_HPP

#include <QtCore/QTextStream>
#include <QUdpSocket>
#include <QWidget>

class UdpNetwork : public QWidget {
    Q_OBJECT
public:
    UdpNetwork(std::string &host, int port);
    ~UdpNetwork() = default;
    void sendData(std::string data);
    void closeConnection();
    QUdpSocket::SocketState getState();

private slots:
    void handleError(int err);
private:
    QUdpSocket *socket;
};

#endif //CPP_BABEL_2019_UDPNETWORK_HPP
