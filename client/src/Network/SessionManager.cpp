//
// Created by guigui on 9/18/19.
//

#include <iostream>
#include "Network/SessionManager.hpp"

SessionManager::SessionManager(QObject *parent, std::string &host, int port, std::string &username,
                               std::string &localDeviceID,
                               std::string &callID)
        : host(host), port(port), username(username), localDeviceID(localDeviceID), callID(callID), registerOk(false),
        pendingRequest(NONE), pendingResponse(NONE) {
    this->udpNetwork = new TcpNetwork(host, port, SessionManager::manageSipParsing, this);
    this->networkInterface = QNetworkInterface::interfaceFromName(this->getConnectedInterface().c_str());
}

void SessionManager::Subscribe() {
    auto requestLine = std::stringstream();
    requestLine << "SUBSCRIBE sip:" << getUsername() << host << " SIP/2.0\r\n";
    auto CSeq = std::stringstream();
    CSeq << "CSeq: 2 SUBSCRIBE\r\n";
    auto recipientUri = std::stringstream();
    recipientUri << getUsername() << "@" << host << ":" << port;
    SipParams params = {requestLine.str(), CSeq.str(), "", getUsername(), recipientUri.str()};
    this->pendingRequest = SUBSCRIBE;
    this->udpNetwork->sendData(this->createSipPacket(params));
}

void SessionManager::Register() {
    auto requestLine = std::stringstream();
    requestLine << "REGISTER sip:" << host << " SIP/2.0\r\n";
    auto CSeq = std::stringstream();
    CSeq << "CSeq: 2 REGISTER\r\n";
    auto recipientUri = std::stringstream();
    recipientUri << getUsername() << "@" << host << ":" << port;
    SipParams params = {requestLine.str(), CSeq.str(), "", getUsername(), recipientUri.str()};
    this->pendingRequest = REGISTER;
    this->udpNetwork->sendData(this->createSipPacket(params));
}

std::string SessionManager::getConnectedInterface() {
    QList<QString> possibleMatches;
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    if ( !ifaces.isEmpty() ) {
        for (auto & iface : ifaces) {
            unsigned int flags = iface.flags();
            bool isLoopback = (bool)(flags & QNetworkInterface::IsLoopBack);
            bool isP2P = (bool)(flags & QNetworkInterface::IsPointToPoint);
            bool isRunning = (bool)(flags & QNetworkInterface::IsRunning);
            if ( !isRunning ) continue;
            if ( !iface.isValid() || isLoopback || isP2P ) continue;
            QList<QHostAddress> addresses = iface.allAddresses();
            for (auto & address : addresses) {
                if (address == QHostAddress::LocalHost ) continue;
                if ( !address.toIPv4Address() ) continue;
                QString ip = address.toString();
                if ( ip.isEmpty() ) continue;
                bool foundMatch = false;
                for (const auto & possibleMatch : possibleMatches) if (ip == possibleMatch ) { foundMatch = true; break;}
                return (iface.name().toStdString());
            }
        }
    }
    return ("wlp58s0");
}

TcpNetwork * SessionManager::getTcpNetwork() const {
    return udpNetwork;
}

const std::string &SessionManager::getUsername() const {
    return username;
}

std::string SessionManager::createSipPacket(SipParams &params) {
    auto ss = std::stringstream();
    ss << params.requestOrStatusLine;
    ss << "Via: SIP/2.0/TCP " << getTcpNetwork()->getLocalHostWithDomain() << "\r\n";
    ss << "To: \"" << params.recipient << "\"<sip:" << params.recipientUri << ">\r\n";
    ss << "From: \"" << getUsername() << "\"<sip:" << getUsername() << "@" << getTcpNetwork()->getLocalHostWithDomain() << ">;tag=" << this->localDeviceID << "\r\n";
    ss << "Call-ID: " << this->callID << "\r\n";
    ss << params.CSeq;
    ss << "Content-Length: " << params.data.length() << "\r\n";
    if (params.data.length())
        ss << "\r\n" << params.data << "\r\n\t";
    return (ss.str());
}

void SessionManager::sendMessage(const std::string &message, const std::string &target) {
    auto requestLine = std::stringstream();
    requestLine << "MESSAGE sip:" << target << "@babel.com SIP/2.0\r\n";
    auto CSeq = std::stringstream();
    CSeq << "CSeq: 1 MESSAGE\r\n";
    auto targetUri = target;
    SipParams params = {requestLine.str(), CSeq.str(), message, target, targetUri};
    this->udpNetwork->sendData(this->createSipPacket(params));
}

void SessionManager::sendOk(std::string codeSeq) {
    auto statusLine = std::string("200 OK\r\n");
    auto CSeq = std::stringstream();
    CSeq << "CSeq: "<< codeSeq << "\r\n";
    auto recipientUri = std::stringstream();
    recipientUri << getUsername() << "@" << host << ":" << port;
    SipParams params = {statusLine, CSeq.str(), "", getUsername(), recipientUri.str()};
    this->udpNetwork->sendData(this->createSipPacket(params));
}

void SessionManager::Update() {
    auto requestLine = std::stringstream();
    requestLine << "UPDATE sip:" << host << " SIP/2.0\r\n";
    auto CSeq = std::stringstream();
    CSeq << "CSeq: UPDATE\r\n";
    auto recipientUri = std::stringstream();
    recipientUri << getUsername() << "@" << host << ":" << port;
    SipParams params = {requestLine.str(), CSeq.str(), "", getUsername(), recipientUri.str()};
    this->pendingRequest = UPDATE;
    this->udpNetwork->sendData(this->createSipPacket(params));
}

void SessionManager::AddFriend(const ContactDetails details) {
    auto requestLine = std::stringstream();
    requestLine << "ADD_FRIEND sip:" << host << " SIP/2.0\r\n";
    auto CSeq = std::stringstream();
    CSeq << "CSeq: ADD_FRIEND\r\n";
    auto recipientUri = std::stringstream();
    recipientUri << getUsername() << "@" << host << ":" << port;
    auto content = std::stringstream();
    content << "Message_Waiting: " << details.name;
    SipParams params = {requestLine.str(), CSeq.str(), content.str(), getUsername(), recipientUri.str()};
    this->pendingRequest = ADD_FRIEND;
    this->udpNetwork->sendData(this->createSipPacket(params));
}

void SessionManager::parsePacket(const std::string packet) {
    std::vector<std::string> lines;
    std::vector<std::string> tmp;
    SipParsedMessage receivedMessage = {UNKNOWN, "", packet, -1};
    boost::split(lines, packet, boost::is_any_of("\r\n"));
    for (int i = 0; lines.size() > i; i++) {
        if (i == 0) {   //start-line
            boost::split(tmp, lines[i], boost::is_any_of(" "));
            try {
                receivedMessage.status = std::stoi(tmp[0]);
                receivedMessage.type = RESPONSE;
            } catch (std::invalid_argument) {
                receivedMessage.request = tmp[0];
                receivedMessage.type = REQUEST;
            }
        }
    }
    this->analyzeParsedMessage(receivedMessage);
}

void SessionManager::manageSipParsing(std::string input, SessionManager *session) {
    session->parseMultiplePacket(input);
}

void SessionManager::analyzeParsedMessage(SipParsedMessage &parsedMessage) {
    if (!this->registerOk)
        return this->handleRegister(parsedMessage);
    if (parsedMessage.type == RESPONSE) {
        if (parsedMessage.status == 100)
            return;
        if (parsedMessage.status == 242) {
            this->parseAllContact(parsedMessage);
            return;
        }
    }
}

void SessionManager::handleRegister(SipParsedMessage &parsedMessage) {
    if (parsedMessage.status == 100)
        return;
    if (parsedMessage.status == 200) {
        this->registerOk = true;
        qDebug() << "regiter ok \n";
        emit RegisterDone();
        this->pendingRequest = NONE;
        //this->Subscribe();
    }
}

bool SessionManager::isRegisterOk() const {
    return registerOk;
}

void SessionManager::parseMultiplePacket(const std::string multiplePacket) {
    std::vector<std::string> lines;
    std::vector<std::string> tmp;
    SipParsedMessage receivedMessage = {UNKNOWN, "", multiplePacket, -1, ""};
    boost::split(lines, multiplePacket, boost::is_any_of("\t"));
    std::cout << lines.size();
    for (const auto& elem : lines)
        !elem.empty() ? this->parsePacket(elem) : void();
}

void SessionManager::parseAllContact(SipParsedMessage &parsedMessage) {
    this->getMessageContent(parsedMessage);
    std::vector<std::string> potentialUser;
    std::vector<std::string> tmpInfos;
    std::vector<ContactDetails> newAllContacts;
    int tmpStatus = 0;
    boost::split(potentialUser, parsedMessage.content, boost::is_any_of(","));
    for (const auto &elem : potentialUser) {
        boost::split(tmpInfos, elem, boost::is_any_of(";"));
        if (tmpInfos.size() == 3) {
            try {
                tmpStatus = std::stoi(tmpInfos[2]);
                newAllContacts.push_back({tmpInfos[0], tmpInfos[1], tmpStatus != 0});
            } catch (std::invalid_argument) {
                continue;
            }
        }
    }
    qDebug() << "Found " << newAllContacts.size() << "contacts\n";
    for (const auto &contact : newAllContacts) {
        qDebug() << contact.name.c_str() << " ";
    }
    qDebug() << "\n";
    this->allContacts = newAllContacts;
    emit UpdateDone(newAllContacts);
}

void SessionManager::getMessageContent(SipParsedMessage &parsedMessage) {
    std::vector<std::string> lines;
    boost::split(lines, parsedMessage.packet, boost::is_any_of("\r\n"));
    for (const auto& elem : lines) {
        if (elem.substr(0, 17) == "Message_Waiting: ") {
            parsedMessage.content = elem.substr(17);
            return;
        }
    }
}

const std::vector<ContactDetails> &SessionManager::getAllContacts() const {
    return allContacts;
}

const std::vector<ContactDetails> &SessionManager::getAllFriends() const {
    return allFriends;
}

void SessionManager::Info() {
    auto requestLine = std::stringstream();
    requestLine << "INFO sip:" << host << " SIP/2.0\r\n";
    auto CSeq = std::stringstream();
    CSeq << "CSeq: INFO\r\n";
    auto recipientUri = std::stringstream();
    recipientUri << getUsername() << "@" << host << ":" << port;
    SipParams params = {requestLine.str(), CSeq.str(), "", getUsername(), recipientUri.str()};
    this->pendingRequest = INFO;
    this->udpNetwork->sendData(this->createSipPacket(params));
}
