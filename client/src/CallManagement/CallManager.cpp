//
// Created by guigui on 10/11/19.
//

#include "CallManagement/CallManager.hpp"

CallManager::CallManager(AsyncSession &session) : session(session), serverInited(false) {
    this->isAwaitingInvite = false;
    this->mode = NO_MODE;
    this->listeningPort = -1;
    connect(&this->session, SIGNAL(InvitedLeftDone(const std::string)), this, SLOT(handlePeopleRefuse(const std::string)));
    connect(&this->session, SIGNAL(InvitedJoinDone(const std::string)), this, SLOT(handlePeopleJoin(const std::string)));
    connect(&this->soundManager, SIGNAL(soundAvailable(const AudioSettings::Encoded)), this, SLOT(sendSound(const AudioSettings::Encoded)));
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
    this->socket = new UdpNetwork(ip, port, nullptr, nullptr);
    qDebug() << name.c_str() << "@" << ip.c_str() << ":" << port << " call joined\r\n";
    // TODO voice transmission
    this->socket->sendData("client connected in P2P\r\n");
    this->session.asyncAck(name);
}

void CallManager::declineCall(std::string &name) {
    this->session.asyncCancel(name);
}

void CallManager::handlePeopleRefuse(const std::string &name) {
    qDebug() << name.c_str() << " refused the call\r\n";
    this->friendsPendingResponse --;
    if (this->friendsPendingResponse == 0 && this->friendsInCall == 0)
        emit callTerminated();
}

void CallManager::handlePeopleJoin(const std::string &name) {
    qDebug() << name.c_str() << " join the call \r\n";
    this->friendsInCall ++;
    this->friendsPendingResponse --;
}

void CallManager::sendSound(const AudioSettings::Encoded &sound) {
    SoundPacket soundPacket;
    soundPacket.magic_code = 0x150407CA;
    soundPacket.soundSize = sound.size;
    std::memset(soundPacket.sound, 0, sizeof(soundPacket.sound));
    std::memcpy(soundPacket.sound, sound.buffer.data(), sound.size);
    soundPacket.timestamp = QDateTime::currentDateTime().toTime_t();
    std::string tmpMsg(reinterpret_cast<char *>(&soundPacket), reinterpret_cast<char *>(&soundPacket + 1));
    this->socket->sendData(tmpMsg);
}
