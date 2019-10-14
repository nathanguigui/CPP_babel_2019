//
// Created by guigui on 10/11/19.
//

#include "CallManagement/CallManager.hpp"

CallManager::CallManager(AsyncSession &session) : session(session), serverInited(false) {
    this->isAwaitingInvite = false;
    this->mode = NO_MODE;
    this->listeningPort = -1;
    qDebug() << "pas encore crash dans le call manager";
    qRegisterMetaType<AudioSettings::Encoded>("encoded_audio");
    connect(&this->session, SIGNAL(InvitedLeftDone(const std::string)), this, SLOT(handlePeopleRefuse(const std::string)));
    connect(&this->session, SIGNAL(InvitedJoinDone(const std::string)), this, SLOT(handlePeopleJoin(const std::string)));
    /// Connect encoded recorded sound to network
    connect(&this->soundManager, SIGNAL(soundAvailable(const AudioSettings::Encoded)), this, SLOT(sendSound(const AudioSettings::Encoded)));
    /// Connect received encoded sound to EncodeManager then to Output Device
    //connect(this->socket, SIGNAL(PacketRecieved(const AudioSettings::Encoded)), &this->soundManager, SLOT(playSound(const AudioSettings::Encoded)));
    qDebug() << "pas encore crash dans le call manager";
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
    this->socket->sendData("hello world");
    // TODO start voice transmission when you connect to the host
    this->soundManager.startRecording();
    //this->soundManager.startPlaying();
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
    // TODO start voice transmission when you are the host
    this->soundManager.startRecording();
    this->soundManager.startPlaying();
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
