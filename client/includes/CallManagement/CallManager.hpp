//
// Created by guigui on 10/11/19.
//

#ifndef CPP_BABEL_2019_CALLMANAGER_HPP
#define CPP_BABEL_2019_CALLMANAGER_HPP

#include "Network/AsyncSession.hpp"
#include "Network/UdpNetwork.hpp"

Q_DECLARE_METATYPE(int)

class CallManager : public QObject {
    Q_OBJECT
public:
    CallManager(AsyncSession &session);
    void makeCall(std::string &name);
    void joinCall(std::string &name, std::string &ip, int port);
    void declineCall(std::string &name);
    ~CallManager() = default;

public slots:
    void asyncServerReady(int port);

private:
    AsyncSession &session;
    std::string awaitInviteName;
    bool isAwaitingInvite;
    bool serverInited;
    UdpNetwork *socket;
    UdpNetworkMode mode;
    int listeningPort;
};

#endif //CPP_BABEL_2019_CALLMANAGER_HPP
