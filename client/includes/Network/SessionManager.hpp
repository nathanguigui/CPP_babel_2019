//
// Created by guigui on 9/18/19.
//

#ifndef CPP_BABEL_2019_SESSIONMANAGER_HPP
#define CPP_BABEL_2019_SESSIONMANAGER_HPP

#include "TcpNetwork.hpp"
#include <QtNetwork/QtNetwork>
#include <boost/algorithm/string.hpp>
#include "mainWindow.hpp"

struct SipParams {
    const std::string &requestOrStatusLine;
    const std::string &CSeq;
    const std::string &data;
    const std::string &recipient;
    const std::string &recipientUri;
};

enum MessageType {
    UNKNOWN,
    REQUEST,
    RESPONSE
};

enum RequestType {
    NONE,
    REGISTER,
    INVITE,
    ACK,
    CANCEL,
    BYE,
    SUBSCRIBE,
    NOTIFY,
    MESSAGE,
    INFO,
    UPDATE,
    OPTIONS,
};

struct SipParsedMessage {
    MessageType type;
    std::string request;
    std::string packet;
    int status;
    std::string content;
};

struct ContactDetails {
    std::string name;
    std::string ip;
    bool connected;
};

class SessionManager {
public:
    SessionManager(std::string &host, int port, std::string &username, std::string &localDeviceID, std::string &callID,
                   MainWindow *parent);
    ~SessionManager() = default;
    void Register();
    void Subscribe();
    void Update();
    void sendMessage(const std::string &message, const std::string &target);
    const std::string &getUsername() const;
    TcpNetwork * getTcpNetwork() const;
    static void manageSipParsing(std::string input, SessionManager *session);
    bool isRegisterOk() const;
    void updateData();
private:
    void parsePacket(const std::string packet);
    void getMessageContent(SipParsedMessage &parsedMessage);
    void sendOk(std::string codeSeq);
    void analyzeParsedMessage(SipParsedMessage &parsedMessage);
    void handleRegister(SipParsedMessage &parsedMessage);
    void parseMultiplePacket(const std::string multiplePacket);
    void parseAllContact(SipParsedMessage &parsedMessage);
    std::string createSipPacket(SipParams &params);
    std::string getConnectedInterface();
    TcpNetwork *udpNetwork;
    std::string host;
    std::string username;
    std::string localDeviceID;
    std::string callID;
    int port;
    QNetworkInterface networkInterface;

    bool registerOk;
    RequestType pendingRequest;
    RequestType pendingResponse;
    std::vector<ContactDetails> allContacts;
public:
    const std::vector<ContactDetails> &getAllContacts() const;

    const std::vector<ContactDetails> &getAllFriends() const;

private:
    std::vector<ContactDetails> allFriends;
    MainWindow *Parent;
};

#endif //CPP_BABEL_2019_SESSIONMANAGER_HPP
