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
    connect(this, SIGNAL(AddFriendRequested(const std::string &)), &session, SLOT(AddFriend(const std::string &)));
    /// Response signals
    connect(&session, SIGNAL(RegisterDone()), this, SIGNAL(RegisterDone()));
    connect(&session, SIGNAL(UpdateDone(std::vector<ContactDetails>)), this, SIGNAL(UpdateDone(std::vector<ContactDetails>)));
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