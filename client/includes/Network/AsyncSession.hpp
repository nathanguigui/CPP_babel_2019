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
    void asyncAddFriend(const ContactDetails details);
    /// Async Update request
    void asyncUpdate();
    /// Async Info request
    void asyncInfo();
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
    void AddFriendRequested(const ContactDetails details);
    /// Signal to tell AddFriend succeed
    void AddFriendDone(const ContactDetails details);
    /// Signal with worker thread
    void InfoRequested();
    /// Signal to tell Info succeed
    void InfoDone(std::vector<ContactDetails>);

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
