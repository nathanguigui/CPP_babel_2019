//
// Created by guigui on 9/18/19.
//

#ifndef CPP_BABEL_2019_SIPMANAGER_HPP
#define CPP_BABEL_2019_SIPMANAGER_HPP

#include "Network/UdpNetwork.hpp"
#include <QtNetwork/QtNetwork>

class SipManager {
public:
    SipManager(std::string &host, int port, std::string &username, std::string &localDeviceID, std::string &callID);
    ~SipManager() = default;
    void Register();
    const std::string &getUsername() const;
    UdpNetwork *getUdpNetwork() const;

private:
    std::string getConnedtedInterface();
    UdpNetwork *udpNetwork;
    std::string host;
    std::string username;
    std::string localDeviceID;
    std::string callID;
    int port;
    QNetworkInterface networkInterface;
};

#endif //CPP_BABEL_2019_SIPMANAGER_HPP
