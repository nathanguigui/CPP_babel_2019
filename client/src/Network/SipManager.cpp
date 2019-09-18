//
// Created by guigui on 9/18/19.
//

#include <sstream>
#include "Network/SipManager.hpp"

SipManager::SipManager(std::string &host, int port, std::string &username, std::string &localDeviceID,
                       std::string &callID)
        : host(host), port(port), username(username), localDeviceID(localDeviceID), callID(callID) {
    this->udpNetwork = new UdpNetwork(host, port);
    this->networkInterface = QNetworkInterface::interfaceFromName(this->getConnedtedInterface().c_str());
}

void SipManager::Register() {
    auto ss = std::stringstream();
    ss << "REGISTER sip:" << host << " SIP/2.0\r\n";
    ss << "Via: SIP/2.0/UDP " << getUdpNetwork()->getLocalHostWithDomain() << "\r\n";
    ss << "To: \"Test\"<sip:" << getUsername() << "@" << host << ":" << port << ">\r\n";
    ss << "From: \"Test\"<sip:" << getUsername() << "@" << getUdpNetwork()->getLocalHostWithDomain() << ">;tag=" << this->localDeviceID << "\r\n";
    ss << "Call-ID: " << this->callID << "\r\n";
    ss << "CSeq: 2 REGISTER\r\n";
    this->udpNetwork->sendData(ss.str());
}

std::string SipManager::getConnedtedInterface() {
    return std::string("wlp58s0");
}

UdpNetwork *SipManager::getUdpNetwork() const {
    return udpNetwork;
}

const std::string &SipManager::getUsername() const {
    return username;
}
