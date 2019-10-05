//
// Created by guigui on 9/18/19.
//

#include <sstream>
#include <iostream>
#include "Network/SessionManager.hpp"

SessionManager::SessionManager(std::string &host, int port, std::string &username, std::string &localDeviceID,
                               std::string &callID)
        : host(host), port(port), username(username), localDeviceID(localDeviceID), callID(callID), registerOk(false),
        pendingRequest(NONE), pendingResponse(NONE) {
    this->udpNetwork = new TcpNetwork(host, port, SessionManager::manageSipParsing, this);
    this->networkInterface = QNetworkInterface::interfaceFromName(this->getConnectedInterface().c_str());
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
        ss << "\r\n" << params.data << "\r\n";
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
    std::cout << "begin of the packet:\r\n" << packet << "\r\n\r\n";
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
    }
}

void SessionManager::handleRegister(SipParsedMessage &parsedMessage) {
    if (parsedMessage.status == 100) {
        this->pendingRequest = NONE;
        return;
    }
    if (parsedMessage.status == 200) {
        this->registerOk = true;
    }
}

bool SessionManager::isRegisterOk() const {
    return registerOk;
}

void SessionManager::parseMultiplePacket(const std::string multiplePacket) {
    std::vector<std::string> lines;
    std::vector<std::string> tmp;
    SipParsedMessage receivedMessage = {UNKNOWN, "", multiplePacket, -1};
    boost::split(lines, multiplePacket, boost::is_any_of("\t"));
    std::cout << lines.size();
    for (const auto& elem : lines)
        this->parsePacket(elem);
}
