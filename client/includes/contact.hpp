//
// Created by glithaud on 10/2/19.
//

#ifndef CPP_BABEL_2019_CONTACT_HPP
#define CPP_BABEL_2019_CONTACT_HPP

#include <QCoreApplication>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QtCore/QDebug>
#include <QtWidgets/QtWidgets>
#include <iostream>
#include <QSize>
#include <QTextEdit>
#include <QSplashScreen>
#include <QTimer>
#include <QMovie>
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QApplication>
#include <vector>
#include "mainWindow.hpp"

class contact : public QWidget
{
public:
    explicit contact(QString login, QString ip, bool state, QWidget *parent = 0);
    ~contact();

    void setMainWindow(MainWindow *m) {mainWindow_ = m;}; // APPELER A CHAQUE NOUvEAU CONTACT
    void setCallState(bool b) {callState_ = b;};
    void setState(bool b) {state_ = b;};
    void setIp(QString ip) { ip_ = ip; };
    bool getCallState() const { return callState_;};
    bool getState() const {return state_; };
    std::vector<QString> getMessages() { return messages; };
    QString getIp() const { return ip_; };
    ///Message from = 0 = send, from = 1 = receive
    void addMessage(std::string message, int from);
    ///CallContact
    void incomingCall();

private:
    bool callState_;
    MainWindow *mainWindow_;
    QString loginName_;
    QString ip_;
    bool state_;
    std::vector<QString> messages;
};

#endif //CPP_BABEL_2019_CONTACT_HPP
