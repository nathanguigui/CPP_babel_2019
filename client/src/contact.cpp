//
// Created by glithaud on 10/2/19.
//

#include "contact.hpp"

contact::contact(QString login, QString ip, bool state, QWidget *parent)
    : loginName_(login), ip_(ip), state_(state), QWidget(parent)
{
    callState_ = false;
    qDebug() <<"login Name : " << loginName_ << " IP : " << ip_;
}


void contact::addMessage(std::string message, int from) {
    QString newMessage;
    if (from == 0) {
        newMessage = QString("to: %1").arg(QString::fromStdString(message));
        qDebug() << newMessage;
        messages.push_back(newMessage);
    } else {
        newMessage = QString("from : %1").arg(QString::fromStdString(message));
        messages.push_back(newMessage);
    }
}
contact::~contact() {

}

void contact::incomingCall()
{
    mainWindow_->incomingCall(loginName_.toStdString());
}