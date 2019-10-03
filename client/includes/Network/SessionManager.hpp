//
// Created by guigui on 9/18/19.
//

#ifndef CPP_BABEL_2019_SESSIONMANAGER_HPP
#define CPP_BABEL_2019_SESSIONMANAGER_HPP

#include "Network/TcpNetwork.hpp"
#include <QtNetwork/QtNetwork>
#include <boost/algorithm/string.hpp>

struct SipParams {
    const std::string &requestOrStatusLine;
    const std::string &CSeq;
    const std::string &data;
    const std::string &recipient;
};

class SessionManager {
public:
    SessionManager(std::string &host, int port, std::string &username, std::string &localDeviceID, std::string &callID);
    ~SessionManager() = default;
    void Register();
    void sendMessage(const std::string &message, const std::string &target);
    const std::string &getUsername() const;
    TcpNetwork * getTcpNetwork() const;

private:
    void parsePacket(std::string &packet);
    std::string getConnectedInterface();
    std::string
    createSipPacket(SipParams &params);
    TcpNetwork *udpNetwork;
    std::string host;
    std::string username;
    std::string localDeviceID;
    std::string callID;
    int port;
    QNetworkInterface networkInterface;
};

#endif //CPP_BABEL_2019_SESSIONMANAGER_HPP
