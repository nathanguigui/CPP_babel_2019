//
// Created by guigui on 10/11/19.
//

#include "CallManagement/CallManager.hpp"

CallManager::CallManager(AsyncSession &session) : session(session) {
    this->isAwaitingInvite = false;
    this->mode = NO_MODE;
    this->listeningPort = -1;
    connect(&this->session, SIGNAL(InvitedLeft(std::string)), this, SLOT(handlePeopleRefuse(std::string)));
    connect(&this->session, SIGNAL(InvitedJoin(std::string)), this, SLOT(handlePeopleJoin(std::string)));
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
    } else {
        this->session.asyncInvite(name, this->listeningPort);
        this->friendsPendingResponse ++;
    }
}

void CallManager::asyncServerReady(int port) {
    this->listeningPort = port;
    qDebug() << "recieved signal\r\n";
    this->session.asyncInvite(this->awaitInviteName, port);
    this->friendsPendingResponse ++;
}

void CallManager::joinCall(std::string &name, std::string &ip, int port) {
    this->socket = new UdpNetwork(ip, port);
    // TODO voice transmission
    this->session.asyncAck(name);
}

void CallManager::declineCall(std::string &name) {
    this->session.asyncCancel(name);
}

void CallManager::handlePeopleRefuse(std::string &name) {
    qDebug() << name.c_str() << " refused the call\r\n";
    this->friendsPendingResponse --;
    if (this->friendsPendingResponse == 0 && this->friendsInCall == 0)
        emit callTerminated();
}

void CallManager::handlePeopleJoin(std::string &name) {
    qDebug() << name.c_str() << " join the call \r\n";
    this->friendsInCall ++;
    this->friendsPendingResponse --;
}
