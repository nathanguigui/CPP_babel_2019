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
        this->awaitInviteName = name;
        this->socket = new UdpNetwork();
        connect(this->socket, SIGNAL(ServerReady(int)), this, SLOT(asyncServerReady(int)));
        this->socket->startServer();
        this->serverInited = true;
        this->mode = SERVER;
        this->isAwaitingInvite = true;
        this->socket = new UdpNetwork();
    } else
        this->session.asyncInvite(name, this->listeningPort);
}

void CallManager::asyncServerReady(int port) {
    this->listeningPort = port;
    qDebug() << "recieved signal\r\n";
    this->session.asyncInvite(this->awaitInviteName, port);
}

void CallManager::joinCall(std::string &name, std::string &ip, int port) {
    this->session.asyncAck(name);
}

void CallManager::declineCall(std::string &name) {
    this->session.asyncCancel(name);
}
