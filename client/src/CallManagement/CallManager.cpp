//
// Created by guigui on 10/11/19.
//

#include "CallManagement/CallManager.hpp"

CallManager::CallManager(AsyncSession &session) : session(session) {
    this->isAwaitingInvite = false;
    this->mode = NO_MODE;
    this->listeningPort = -1;
}

void CallManager::makeCall(std::string &name) {
    if (!this->serverInited) {
        this->socket = new UdpNetwork();
        this->serverInited = true;
        connect(this->socket, SIGNAL(ServerReady(int)), this, SLOT(asyncServerReady(int)));
        this->mode = SERVER;
        this->isAwaitingInvite = true;
        this->awaitInviteName = name;
    } else
        this->session.asyncInvite(name, this->listeningPort);
}

void CallManager::asyncServerReady(int port) {
    this->listeningPort = port;
    this->session.asyncInvite(this->awaitInviteName, port);

}
