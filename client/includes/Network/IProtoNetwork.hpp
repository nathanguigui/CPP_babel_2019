//
// Created by guigui on 9/25/19.
//

#ifndef CPP_BABEL_2019_IPROTONETWORK_HPP
#define CPP_BABEL_2019_IPROTONETWORK_HPP

#include <QtCore/QtCore>

class IProtoNetwork {
public:

    virtual void sendData(std::string data) = 0;

    virtual void closeConnection() = 0;

    virtual const std::string &getConnectedHostname() const = 0;

    virtual int getConnectedPort() const = 0;

    virtual const std::string getLocalIp() const = 0;

    virtual std::string getConnectedHostWithDomain() const = 0;

    virtual std::string getLocalHostWithDomain() const = 0;

    virtual quint16 getLocalPort() const = 0;
};

#endif //CPP_BABEL_2019_IPROTONETWORK_HPP
