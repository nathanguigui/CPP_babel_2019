//
// Created by glithaud on 10/2/19.
//

#include "../includes/contact.hpp"

contact::contact(QString login, QString ip, bool state, QWidget *parent)
    : loginName_(login), ip_(ip), state_(state), QWidget(parent)
{
    qDebug() <<"login Name : " << loginName_ << " IP : " << ip_;
}

contact::~contact() {

}