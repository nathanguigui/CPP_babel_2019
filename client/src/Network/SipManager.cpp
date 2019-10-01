//
// Created by guigui on 9/18/19.
//

#include <sstream>
#include <iostream>
#include "Network/SipManager.hpp"

SipManager::SipManager(std::string &host, int port, std::string &username, std::string &localDeviceID,
                       std::string &callID)
        : host(host), port(port), username(username), localDeviceID(localDeviceID), callID(callID) {
    this->udpNetwork = new TcpNetwork(host, port);
    this->networkInterface = QNetworkInterface::interfaceFromName(this->getConnedtedInterface().c_str());
}

void SipManager::Register() {
    auto requestLine = std::stringstream();
    requestLine << "REGISTER sip:" << host << " SIP/2.0\r\n";
    auto CSeq = std::stringstream();
    CSeq << "CSeq: 2 REGISTER\r\n";
    this->udpNetwork->sendData(this->createSipPacket(requestLine.str(), CSeq.str()));

}

std::string SipManager::getConnedtedInterface() {
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

TcpNetwork * SipManager::getTcpNetwork() const {
    return udpNetwork;
}

const std::string &SipManager::getUsername() const {
    return username;
}

std::string SipManager::createSipPacket(const std::string& requestOrStatusLine, const std::string& CSeq) {
    auto ss = std::stringstream();
    ss << requestOrStatusLine;
    ss << "Via: SIP/2.0/UDP " << getTcpNetwork()->getLocalHostWithDomain() << "\r\n";
    ss << "To: \"Test\"<sip:" << getUsername() << "@" << host << ":" << port << ">\r\n";
    ss << "From: \"Test\"<sip:" << getUsername() << "@" << getTcpNetwork()->getLocalHostWithDomain() << ">;tag=" << this->localDeviceID << "\r\n";
    ss << "Call-ID: " << this->callID << "\r\n";
    ss << CSeq;
    return (ss.str());
}
