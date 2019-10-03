//
// Created by guigui on 9/18/19.
//

#ifndef CPP_BABEL_2019_SIPMANAGER_HPP
#define CPP_BABEL_2019_SIPMANAGER_HPP

#include "Network/TcpNetwork.hpp"
#include <QtNetwork/QtNetwork>

class SipManager {
public:
    SipManager(std::string &host, int port, std::string &username, std::string &localDeviceID, std::string &callID);
    ~SipManager() = default;
    void Register();
    const std::string &getUsername() const;
    TcpNetwork * getTcpNetwork() const;

private:
    std::string getConnedtedInterface();
    std::string createSipPacket(const std::string& requestOrStatusLine, const std::string& CSeq);
    TcpNetwork *udpNetwork;
    std::string host;
    std::string username;
    std::string localDeviceID;
    std::string callID;
    int port;
    QNetworkInterface networkInterface;
};

#endif //CPP_BABEL_2019_SIPMANAGER_HPP
