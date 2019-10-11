//
// Created by guigui on 9/18/19.
//

#ifndef CPP_BABEL_2019_SESSIONMANAGER_HPP
#define CPP_BABEL_2019_SESSIONMANAGER_HPP

#include "TcpNetwork.hpp"
#include <QtNetwork/QtNetwork>
#include <boost/algorithm/string.hpp>

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
    ADD_FRIEND
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

class SessionManager : public QObject {
    Q_OBJECT
public:
    SessionManager(QObject *parent, std::string &host, int port, std::string &username, std::string &localDeviceID,
                   std::string &callID);
    ~SessionManager() = default;

public slots:
    /// Send Register request
    void Register();
    /// Send Subscribe request to receive notifications
    void Subscribe();
    /// Send Update Request to get the list of all contacts
    void Update();
    /// Send Info Request to get the list of all friends
    void Info();
    /// Send message with Message Request to contact
    void sendMessage(const std::string &message, const std::string &target);
    /// Send AddFriend Request to add a friend
    void AddFriend(const std::string &name);
    /// Send Bye Request to tell server the client will disconnect
    void Bye();
    /// Send Invite Request to make call
    void Invite(const std::string &name, int listeningPort);

signals:
    /// Signal to tell auth completed
    void RegisterDone();
    /// Signal to tell AddFriend succeed
    void AddFriendDone(const std::string &name);
    /// Signal to tell Update completed
    void UpdateDone(std::vector<ContactDetails>);
    /// Signal to tell Info completed
    void InfoDone(std::vector<ContactDetails>);
    /// Signal to tell someone is calling
    void InvitedRinging(const std::string name, const std::string ip, int port);

public:
    const std::string &getUsername() const;

    TcpNetwork * getTcpNetwork() const;

    static void manageSipParsing(std::string input, SessionManager *session);
    /// Return true if User is registered
    bool isRegisterOk() const;
    /// Return the list of all contact present in the server
    const std::vector<ContactDetails> &getAllContacts() const;
    /// Return the list of all friends of the current user
    const std::vector<ContactDetails> &getAllFriends() const;

private:
    void parsePacket(const std::string packet);
    void getMessageContent(SipParsedMessage &parsedMessage);
    void sendOk(std::string codeSeq);
    void analyzeParsedMessage(SipParsedMessage &parsedMessage);
    void handleRegister(SipParsedMessage &parsedMessage);
    void parseMultiplePacket(const std::string multiplePacket);
    void parseContactMessage(SipParsedMessage &parsedMessage, RequestType requestType);
    void parseAllContact(SipParsedMessage &parsedMessage);
    void parseAllFriends(SipParsedMessage &parsedMessage);
    void parseRingPacket(SipParsedMessage &parsedMessage);
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
    std::vector<ContactDetails> allFriends;
};

#endif //CPP_BABEL_2019_SESSIONMANAGER_HPP
