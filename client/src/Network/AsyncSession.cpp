//
// Created by guigui on 10/6/19.
//

#include "Network/AsyncSession.hpp"

AsyncSession::AsyncSession(QObject *parent) {
    m_ready = false;
    port = 25565;
}

void AsyncSession::asyncRegister() {
    emit RegisterRequested();
}

void AsyncSession::asyncAddFriend(const std::string &name) {
    emit AddFriendRequested(name);
}

void AsyncSession::run() {
    SessionManager session(nullptr, host, port, username, localDeviceID, callID);
    qRegisterMetaType<std::string>("std_string");
    qRegisterMetaType<ContactDetails>("contact_details");
    qRegisterMetaType<std::vector<ContactDetails>>("contact_list");
    /// Requests signals
    connect(this, SIGNAL(RegisterRequested()), &session, SLOT(Register()));
    connect(this, SIGNAL(UpdateRequested()), &session, SLOT(Update()));
    connect(this, SIGNAL(InfoRequested()), &session, SLOT(Info()));
    connect(this, SIGNAL(AddFriendRequested(const std::string)), &session, SLOT(AddFriend(const std::string)));
    connect(this, SIGNAL(ByeRequested()), &session, SLOT(Bye()));
    connect(this, SIGNAL(InviteRequested(const std::string, int)), &session, SLOT(Invite(const std::string, int)));
    connect(this, SIGNAL(AckRequested(const std::string)), &session, SLOT(Ack(const std::string)));
    connect(this, SIGNAL(CancelRequested(const std::string)), &session, SLOT(Cancel(const std::string)));
    /// Response signals
    connect(&session, SIGNAL(RegisterDone()), this, SIGNAL(RegisterDone()));
    connect(&session, SIGNAL(UpdateDone(std::vector<ContactDetails>)), this, SIGNAL(UpdateDone(std::vector<ContactDetails>)));
    connect(&session, SIGNAL(InfoDone(std::vector<ContactDetails>)), this, SIGNAL(InfoDone(std::vector<ContactDetails>)));
    connect(&session, SIGNAL(InvitedRinging(const std::string, const std::string, int)), this, SIGNAL(InvitedRinging(const std::string, const std::string, int)));
    connect(&session, SIGNAL(InvitedLeft(const std::string)), this, SLOT(handleLeft(const std::string)));
    connect(&session, SIGNAL(InvitedJoin(const std::string)), this, SLOT(handleJoin(const std::string)));
    this->m_ready = true;
    this->exec();
}

void AsyncSession::asyncUpdate() {
    emit UpdateRequested();
}

void AsyncSession::delayRun(std::string &host, int port, std::string username, std::string &localDeviceID, std::string &callID) {
    this->host = host;
    this->port = port;
    this->username = username;
    this->localDeviceID = localDeviceID;
    this->callID = callID;
    this->start();
    while (!this->m_ready)
        msleep(50);
}

void AsyncSession::asyncInfo() {
    emit InfoRequested();
}

void AsyncSession::asyncBye() {
    emit ByeRequested();
}

void AsyncSession::asyncInvite(const std::string &name, int port) {
    emit InviteRequested(name, port);
}

void AsyncSession::asyncAck(const std::string &name) {
    emit AckRequested(name);
}

void AsyncSession::asyncCancel(const std::string &name) {
    emit CancelRequested(name);
}

void AsyncSession::handleJoin(const std::string &name) {
    qDebug() << name.c_str() << " accepted the call and detected in async session\r\n";
    emit InvitedJoinDone(name);
}

void AsyncSession::handleLeft(const std::string &name) {
    emit InvitedLeftDone(name);
}
