 //
// Created by guigui on 10/6/19.
//

#ifndef CPP_BABEL_2019_ASYNCSESSION_HPP
#define CPP_BABEL_2019_ASYNCSESSION_HPP

#include <QThread>
#include "Network/SessionManager.hpp"

class AsyncSession : public QThread {
    Q_OBJECT
public:
    explicit AsyncSession(QObject *parent = nullptr);

    ~AsyncSession() override = default;
    /// Custom run
    void delayRun(std::string &host, int port, std::string username, std::string &localDeviceID, std::string &callID);
    /// Async Register request
    void asyncRegister();
    /// Async AddFriend request
    void asyncAddFriend(const std::string &name);
    /// Async Update request
    void asyncUpdate();
    /// Async Info request
    void asyncInfo();
    /// Async Bye request
    void asyncBye();
    /// Async Invite request
    void asyncInvite(const std::string &name, int port);

signals:
    /// Signal with worker thread
    void RegisterRequested();
    /// Signal to tell auth completed
    void RegisterDone();
    /// Signal with worker thread
    void UpdateRequested();
    /// Signal to tell auth completed
    void UpdateDone(std::vector<ContactDetails>);
    /// Signal with worker thread
    void AddFriendRequested(const std::string &name);
    /// Signal to tell AddFriend succeed
    void AddFriendDone(const ContactDetails details);
    /// Signal with worker thread
    void InfoRequested();
    /// Signal to tell Info succeed
    void InfoDone(std::vector<ContactDetails>);
    /// Signal with worker thread
    void ByeRequested();

    /// Signal with worker thread to call people
    void InviteRequested(const std::string &name, int port);
    /// Signal with worker thread to tell invited friend is ringing
    void InvitedRinging(const std::string &name);
    /// Signal with worker thread to tell invited friend accepted
    void InvitedAccepted(const std::string &name);

protected:
    void run() override;

private:
    /// Indicate if worker thread is ready
    bool m_ready;
    /// Session variables
    std::string host;
    int port;
    std::string username;
    std::string localDeviceID;
    std::string callID;
};

#endif //CPP_BABEL_2019_ASYNCSESSION_HPP
